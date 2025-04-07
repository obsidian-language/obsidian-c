AUTOMAKE_OPTIONS = subdir-objects

include_HEADERS = include/color.h include/common.h include/error.h include/lexer.h include/parser.h include/ast.h

bin_PROGRAMS = obsidian
obsidian_SOURCES = common.c error.c lexer.c parser.c ast.c obsidian.c

AM_CFLAGS = $(CFLAGS)
