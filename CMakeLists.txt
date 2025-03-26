# ------------------------------------------------------------
# CMake commands - configure then compile
#
# Configure Build 
#       cmake -S . -B build
#
# Compile Build
#       cmake --build build
#
# ------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)
project(obsidian-c LANGUAGES C)
add_executable(obsidian-c src/common.c src/error.c src/lexer.c src/obsidian.c)
