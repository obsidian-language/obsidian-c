#include "include/common.h"
#include "include/lexer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            printVersion();
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            printHelpMenu();
            return EXIT_SUCCESS;
        } else if (strncmp(argv[i], "--help=", 7) == 0) {
            const char *helpTopic = argv[i] + 7;
            if (strcmp(helpTopic, "optimizers") == 0) {
                printOptimizersHelp();
            } else if (strcmp(helpTopic, "target") == 0) {
                printTargetHelp();
            } else if (strcmp(helpTopic, "warnings") == 0) {
                printWarningsHelp();
            } else {
                fprintf(stderr, "unrecognized argument to '--help=' option: '%s'\n", helpTopic);
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }
    }
     
    const char *source = argv[1];
    FILE *file = fopen(source, "r");
    if (file == NULL) {
        fprintf(stderr, "obsidian: error: no input file\n");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    if (buffer == NULL) {
        fprintf(stderr, "obsidian: error: could not allocate memory for file '%s'\n", source);
        return EXIT_FAILURE;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    Lexer lexer;
    initLexer(&lexer, buffer);

    do {
        Token token = getNextToken(&lexer);
        printf("Token: %d\n", token.type);
    } while (!isEndOfFile(&lexer));

    fclose(file);
    free(buffer);

    return 0;
}