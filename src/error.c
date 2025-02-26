#include "include/error.h"
#include "include/color.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int error(const char *message, Token *token) {
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
    fprintf(stderr, "Error: ");
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    fprintf(stderr, "[line ");
    set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    fprintf(stderr, "%d", token->line);
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    fprintf(stderr, ", column ");
    set_color(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    fprintf(stderr, "%d", token->column);
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    fprintf(stderr, "] ");
    set_color(FOREGROUND_RED | FOREGROUND_INTENSITY);
    fprintf(stderr, "%s: %c\n", message, *token->start);
    set_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    fprintf(stderr, LIGHT_RED "Error: " RESET);
    fprintf(stderr, "[line " LIGHT_BLUE "%d" RESET ", column " LIGHT_BLUE "%d" RESET "] ", token->line, token->column);
    fprintf(stderr, LIGHT_RED "%s: " RESET "%c\n", message, *token->start);
#endif
    fprintf(stderr, "    %d | %.*s\n", token->line, (int)(line_end - line_start), line_start);
    fprintf(stderr, "      | ");
    for (int i = 0; i < column_offset; i++) {
        fprintf(stderr, (line_start[i] == '\t') ? "\t" : " ");
    }
    fprintf(stderr, "^\n");

    return EXIT_FAILURE;
}
