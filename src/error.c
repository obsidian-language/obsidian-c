#include "include/error.h"
#include "include/color.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error(const char *message, Token *token) {
    const char *line_start = token->start;
    while (line_start > token->start - token->column && *line_start != '\n') {
        line_start--;
    }
    if (*line_start == '\n') {
        line_start++;
    }

    const char *line_end = token->start;
    while (*line_end != '\n' && *line_end != '\0') {
        line_end++;
    }

#ifdef _WIN32
    set_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
    fprintf(stderr, "Error: ");
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    fprintf(stderr, "[line: ");
    set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    fprintf(stderr, "%d", token->line);
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    fprintf(stderr, ", column: ");
    set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    fprintf(stderr, "%d", token->column);
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    fprintf(stderr, "] ");
    set_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
    fprintf(stderr, "%s: %.*s\n", message, token->length, token->start);
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    fprintf(stderr, "    %d | %.*s\n", token->line, (int)(line_end - line_start), line_start);
    fprintf(stderr, "      | %*s^\n", token->column - 1, "");
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    fprintf(stderr, LIGHT_RED "Error: " RESET);
    fprintf(stderr, "[line: ");
    fprintf(stderr, LIGHT_BLUE "%d" RESET, token->line);
    fprintf(stderr, ", column: ");
    fprintf(stderr, LIGHT_BLUE "%d" RESET, token->column);
    fprintf(stderr, "] ");
    fprintf(stderr, LIGHT_RED "%s: %.*s\n" RESET, message, token->length, token->start);
    fprintf(stderr, "    %d | %.*s\n", token->line, (int)(line_end - line_start), line_start);
    fprintf(stderr, "      | %*s^\n", token->column - 1, "");
#endif
    exit(EXIT_FAILURE);
}