#include "include/error.h"
#include "include/color.h"
#include <stdlib.h>

extern int yylineno;
extern int yycolumn;
extern FILE *yyin;
extern char *yytext;
extern int yyleng;
extern const char *filename;

void print_full_line(FILE *file, int line_number) {
    char line[1024];
    int current_line = 1;

    rewind(file);
    while (fgets(line, sizeof(line), file)) {
        if (current_line == line_number) {
            printf(BLUE "   |\n" WHITE);
            printf(MAGENTA " %d " BLUE "| " GRAY "   %s", line_number, line);
            break;
        }
        current_line++;
    }
}

void report_error(const char* message, const char* text) {
    printf(LIGHT_RED "error" GRAY ": %s: '%s'\n", message, text);
    printf(BLUE "  --> " GRAY "%s:%d:%d\n", filename, yylineno, yycolumn);
    print_full_line(yyin, yylineno);

    fputs(BLUE "   |", stderr);
    for (int i = 0; i < yycolumn + 2; i++) fputc(' ', stderr);
    fputs(LIGHT_RED " ^\n", stderr);

    puts(BLUE "   |" GRAY);
    fprintf(stderr, "Compilation Failed. Exited at code: 1\n");
    exit(1);
}
