/**
 * @file error.c
 * @brief Implements the error handling system for the Obsidian programming language.
 *
 * This file is responsible for managing error reporting and handling within the 
 * Obsidian compiler. It defines error types, messages, and functions to report 
 * errors encountered during compilation and execution.
 * 
 * @author Codezz-ops <codezz-ops@obsidian.cc>
 * 
 * @copyright Copyright (c) 2024 Obsidian Language
 * @license BSD 3-Clause
 */

#include "include/error.h"
#include "include/color.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Converts an ErrorType enum to a string representation.
 * 
 * @param type The ErrorType to convert.
 * @return const char* A string representation of the error type.
 */
const char* errorTypeToString(ErrorType type) {
    switch (type) {
        case LexicalError: return "Lexical Error";
        case SyntaxError: return "Syntax Error";
        case SemanticError: return "Semantic Error";
        default: return "Unknown Error";
    }
}

/**
 * @brief Prints an error message to stderr with context information.
 * 
 * This function formats and displays an error message, including the type of error,
 * the line and column where the error occurred, and a snippet of the source code
 * around the error. It also handles color formatting for terminal output based on
 * the operating system.
 * 
 * @param type The type of error that occurred.
 * @param message A message describing the error.
 * @param token A pointer to the Token structure that contains information about
 *              the location of the error in the source code.
 * @return int Returns EXIT_FAILURE to indicate an error occurred.
 */
int error(ErrorType type, const char *message, Token *token) {
    const char *line_start = token->start;
    const char *line_end = token->start;
    int column_offset;

    while (line_start > token->start - token->column && line_start > token->start - token->column + 1 && *(line_start - 1) != '\n') {
        line_start--;
    }

    while (*line_end != '\n' && *line_end != '\0') {
        line_end++;
    }

    column_offset = (int)(token->start - line_start);

#ifdef _WIN32
    set_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
    fprintf(stderr, "%s: ", errorTypeToString(type));
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    fputs("[line ", stderr);
    set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    fprintf(stderr, "%d", token->line);
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    fputs(", column ", stderr);
    set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    fprintf(stderr, "%d", token->column);
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    fputs("] ", stderr);
    set_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
    fprintf(stderr, "%s: %c\n", message, *token->start);
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    fprintf(stderr, LIGHT_RED "%s: " RESET, errorTypeToString(type));
    fprintf(stderr, "[line " LIGHT_BLUE "%d" RESET ", column " LIGHT_BLUE "%d" RESET "] ", token->line, token->column);
    fprintf(stderr, LIGHT_RED "%s: " RESET "%c\n", message, *token->start);
#endif
    fprintf(stderr, "    %d | %.*s\n", token->line, (int)(line_end - line_start), line_start);
    fputs("      | ", stderr);
    for (int i = 0; i < column_offset; i++) {
        fprintf(stderr, (line_start[i] == '\t') ? "\t" : " ");
    }
    fputs("^\n", stderr);

    return EXIT_FAILURE;
}
