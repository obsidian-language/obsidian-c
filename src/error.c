#include "include/error.h"
#include "include/color.h"

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
