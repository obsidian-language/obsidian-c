cmake_minimum_required(VERSION 3.20)

project(obsidian)

if (WIN32) 
    message("Building on Windows...")
    set(CMAKE_C_FLAGS "-std=c17 -O2 -static -Wfatal-errors -Wextra -Wshadow -Wundef -Wwrite-strings -Wredundant-decls -Wdisabled-optimization -Wdouble-promotion -Wmissing-declarations -Wconversion -Wstrict-overflow=2")
elseif(UNIX)
    message("Building on Unix...")
    set(CMAKE_C_FLAGS "-std=c17 -O2 -Wfatal-errors -Wextra -Wshadow -Wundef -Wwrite-strings -Wredundant-decls -Wdisabled-optimization -Wdouble-promotion -Wmissing-declarations -Wconversion -Wstrict-overflow=2")
endif()

add_executable(obsidian src/obsidian.c src/lexer.c src/common.c src/error.c src/include/lexer.h src/include/common.h src/include/error.h)