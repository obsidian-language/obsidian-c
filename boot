#!/usr/bin/env python3

from subprocess import Popen, run
from textwrap import dedent
from os import getenv, path
from sys import stderr, exit
from re import sub
from platform import system

def print_err(s):
    print(dedent(s), file=stderr)

def die(mesg):
    print_err(mesg)
    exit(1)

def autoreconf():
    processes = {}
    if system() == 'Windows':
        # On Windows, autoreconf doesn't seem to respect the ACLOCAL_PATHwha
        # environment variable, so we need to set it manually.
        ac_local = getenv('ACLOCAL_PATH', '')
        ac_local_arg = sub(r';', r':', ac_local)
        ac_local_arg = sub(r'\\', r'/', ac_local_arg)
        ac_local_arg = sub(r'(\w):/', r'/\1/', ac_local_arg)
        reconf_cmd = 'ACLOCAL_PATH=%s autoreconf -i' % ac_local_arg
    else:
        reconf_cmd = 'autoreconf -i'

    if system() == 'Darwin':
        # On MacOS, autoreconf doesn't seem to respect the aclocal nor
        # automake --add-missing, so we need to set it manually.
        run(['aclocal'], cwd=dir_)

        for dir_ in ['.', 'src']:
            if path.isfile(path.join(dir_, 'configure.ac')):
                print('Running automake --add-missing in %s' % dir_)
                result = run(['automake', '--add-missing'], cwd=dir_)
                if result.returncode != 0:
                    print_err('automake --add-missing in %s failed with exit code %d' % (dir_, result.returncode))
                    exit(1)

    for dir_ in ['.', 'src']:
        # Skip directories that don't have configure.ac
        if path.isfile(path.join(dir_, 'configure.ac')):
            print('Running autoreconf in %s' % dir_)
            processes[dir_] = Popen(['sh', '-c', reconf_cmd], cwd=dir_)

    fail = False
    for k, v in processes.items():
        code = v.wait()
        if code != 0:
            print_err('autoreconf in %s failed with exit code %d' % (k, code))
            fail = True

    if fail:
        exit(1)

autoreconf()