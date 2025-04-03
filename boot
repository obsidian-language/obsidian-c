#!/usr/bin/env python3

from subprocess import Popen, run
from colorama import init, Fore
from textwrap import dedent
from os import getenv, path
from sys import stderr, exit
from re import sub
from platform import system

init(autoreset=True)

def print_err(s):
    print(Fore.RED + f"[ERROR] {Fore.WHITE}{dedent(s)}", file=stderr)

def die(mesg):
    print_err(mesg)
    exit(1)

def log(msg):
    print(Fore.GREEN + f"[INFO] {Fore.WHITE}{msg}")

def warn(msg):
    print(Fore.YELLOW + f"[WARNING] {Fore.WHITE}{msg}")

def autoreconf():
    log("Starting autoreconf process...")
    processes = {}
    
    if system() == 'Windows':
        log("Detected Windows system. Adjusting ACLOCAL_PATH...")
        ac_local = getenv('ACLOCAL_PATH', '')
        ac_local_arg = sub(r';', r':', ac_local)
        ac_local_arg = sub(r'\\', r'/', ac_local_arg)
        ac_local_arg = sub(r'(\w):/', r'/\1/', ac_local_arg)
        reconf_cmd = f'ACLOCAL_PATH={ac_local_arg} autoreconf -i'
    else:
        reconf_cmd = 'autoreconf -i'

    directories = ['.', 'src']
    log(f"Checking directories: {directories}")

    if system() == 'Darwin':
        log("Detected macOS system. Running aclocal...")
        result = run(['aclocal'], cwd='.')
        if result.returncode != 0:
            die(f"aclocal failed with exit code {result.returncode}")
        
        for dir_ in directories:
            if path.isfile(path.join(dir_, 'configure.ac')):
                log(f"Running automake --add-missing in {dir_}...")
                result = run(['automake', '--add-missing'], cwd=dir_)
                if result.returncode != 0:
                    print_err(f"automake --add-missing in {dir_} failed with exit code {result.returncode}")
                    exit(1)
    
    for dir_ in directories:
        if path.isfile(path.join(dir_, 'configure.ac')):
            log(f"Running autoreconf in {dir_}...")
            try:
                processes[dir_] = Popen(['sh', '-c', reconf_cmd], cwd=dir_)
            except FileNotFoundError:
                die(f"autoreconf command not found. Make sure Autotools is installed.")

    fail = False
    for k, v in processes.items():
        log(f"Waiting for autoreconf to complete in {k}...")
        code = v.wait()
        if code != 0:
            print_err(f"autoreconf in {k} failed with exit code {code}")
            fail = True
    
    if fail:
        die("Autoreconf process encountered errors.")
    else:
        log("Autoreconf process completed successfully.")

autoreconf()
