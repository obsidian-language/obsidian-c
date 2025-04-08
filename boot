#!/usr/bin/env python3

import argparse
import os
from subprocess import run, CalledProcessError
from os import remove
from os.path import join, isfile
from sys import stderr, exit
from shutil import which
from colorama import init, Fore

init(autoreset=True)

# Default compiler and linker flags
DEFAULT_CC_FLAGS = [
    "-Wall", "-Wextra", "-Wshadow", "-Wundef", "-Wwrite-strings",
    "-Wredundant-decls", "-Wmissing-declarations", "-Wconversion", "-Wfatal-errors", "-pedantic", "-Wvla",
    "-Wstrict-prototypes", "-fno-strict-aliasing"
]

DEFAULT_LD_FLAGS = [
    "-fPIC", "-s"
]

def print_err(message):
    print(Fore.RED + f"[ERROR] {Fore.WHITE}{message}", file=stderr)

def log(message):
    print(Fore.GREEN + f"[INFO] {Fore.WHITE}{message}")

def check_command(command):
    path = which(command)
    if path is None:
        print_err(f"{command} is not installed or not found in PATH. Please install it before proceeding.")
        exit(1)
    else:
        log(f"Found {command} at {path}")

def compile_sources(sources, output, cc, cc_flags):
    log(f"Compiling sources: {', '.join(sources)}")
    command = [cc] + cc_flags + sources + ['-o', output] + DEFAULT_LD_FLAGS
    log(f"Running: {' '.join(command)}")
    try:
        run(command, check=True)
        log(f"Successfully built {output}")
    except CalledProcessError as e:
        print_err(f"Compilation failed with exit code {e.returncode}")
        exit(1)

def generate_files(args):
    src_dir = 'src'

    if not isfile(join(src_dir, 'parser.tab.c')):
        log("Generating parser.tab.c and parser.tab.h using bison...")
        bison_flags = args.bison_flags if args.bison_flags else []
        bison_cmd = ['bison'] + bison_flags + ['-d', '-o', join(src_dir, 'parser.tab.c'), join(src_dir, 'parser.y')]
        log(f"Running: {' '.join(bison_cmd)}")
        run(bison_cmd, check=True)

    if not isfile(join(src_dir, 'lex.yy.c')):
        log("Generating lex.yy.c using flex...")
        flex_flags = args.flex_flags if args.flex_flags else []
        flex_cmd = ['flex'] + flex_flags + ['-o', join(src_dir, 'lex.yy.c'), join(src_dir, 'lexer.l')]
        log(f"Running: {' '.join(flex_cmd)}")
        run(flex_cmd, check=True)

def build(args):
    src_dir = 'src'
    sources = [
        join(src_dir, 'common.c'),
        join(src_dir, 'obsidian.c'),
        join(src_dir, 'ast.c'),
        join(src_dir, 'parser.tab.c'),
        join(src_dir, 'lex.yy.c'),
    ]
    output = 'obsidian'

    # Merge default flags with user-provided ones
    user_cc_flags = args.cc_flags if args.cc_flags else []
    cc_flags = DEFAULT_CC_FLAGS + user_cc_flags

    generate_files(args)
    compile_sources(sources, output, args.cc, cc_flags)

def rebuild(args):
    log("Rebuilding the project...")
    clean()
    build(args)

def clean():
    log("Cleaning up generated files...")
    files_to_remove = [
        'obsidian',
        'obsidian.exe',
        'src/parser.tab.c',
        'src/parser.tab.h',
        'src/lex.yy.c',
        'src/parser.output'
    ]

    for file in files_to_remove:
        try:
            remove(file)
            log(f"Removed {file}")
        except FileNotFoundError:
            log(f"{file} not found, skipping.")
        except Exception as e:
            print_err(f"Failed to remove {file}: {e}")

def main():
    parser = argparse.ArgumentParser(description="Build script for the project.")
    parser.add_argument('--host', help='Specify the host for cross-compilation.')
    parser.add_argument('--cc', default='gcc', help='Specify the C compiler to use (default: gcc).')
    parser.add_argument('--cc-flags', nargs='*', help='Flags for the C compiler.')
    parser.add_argument('--bison-flags', nargs='*', help='Flags for bison.')
    parser.add_argument('--flex-flags', nargs='*', help='Flags for flex.')
    parser.add_argument('command', nargs='?', default='build', help='Command to execute (default: build).')

    args = parser.parse_args()

    for cmd in ['gcc', 'flex', 'bison']:
        check_command(cmd)

    command_map = {
        'clean': clean,
        'build': lambda: build(args),
        'rebuild': lambda: rebuild(args),
    }

    action = command_map.get(args.command)
    if action:
        action()
    else:
        print_err(f"Unknown command: {args.command}")
        parser.print_help()
        exit(1)

if __name__ == "__main__":
    main()
