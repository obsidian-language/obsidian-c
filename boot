#!/usr/bin/env python3

import os
import os.path
import sys
from textwrap import dedent
import subprocess
import re

def print_err(s):
    print(dedent(s), file=sys.stderr)

def die(mesg):
    print_err(mesg)
    sys.exit(1)

def autoreconf():
    processes = {}
    if os.name == 'nt':
        # On Windows, autoreconf doesn't seem to respect the ACLOCAL_PATH
        # environment variable, so we need to set it manually.
        ac_local = os.getenv('ACLOCAL_PATH', '')
        ac_local_arg = re.sub(r';', r':', ac_local)
        ac_local_arg = re.sub(r'\\', r'/', ac_local_arg)
        ac_local_arg = re.sub(r'(\w):/', r'/\1/', ac_local_arg)
        reconf_cmd = 'ACLOCAL_PATH=%s autoreconf' % ac_local_arg
    else:
        reconf_cmd = 'autoreconf'

    for dir_ in ['.', 'src']:
        if os.path.isfile(os.path.join(dir_, 'configure.ac')):
            print('Running automake --add-missing in %s' % dir_)
            result = subprocess.run(['automake', '--add-missing'], cwd=dir_)
            if result.returncode != 0:
                print_err('automake --add-missing in %s failed with exit code %d' % (dir_, result.returncode))
                sys.exit(1)

    for dir_ in ['.', 'src']:
        # Skip directories that don't have configure.ac
        if os.path.isfile(os.path.join(dir_, 'configure.ac')):
            print('Running autoreconf in %s' % dir_)
            processes[dir_] = subprocess.Popen(['sh', '-c', reconf_cmd], cwd=dir_)

    fail = False
    for k, v in processes.items():
        code = v.wait()
        if code != 0:
            print_err('autoreconf in %s failed with exit code %d' % (k, code))
            fail = True

    if fail:
        sys.exit(1)

autoreconf()