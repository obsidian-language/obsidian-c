#ifdef _WIN32
// Silence deprecation warnings on Windows
#define _CRT_SECURE_NO_WARNINGS
#endif // _WIN32

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/ast.h"
#include "parser.h"
#include "include/common.h"

extern FILE *yyin;
extern ASTNode *root;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fputs("obsidian: error: no input file\n", stderr);
        return EXIT_FAILURE;
    }

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

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "obsidian: error: could not read file '%s'\n", filename);
        return EXIT_FAILURE;
    }

    yyin = file;

    if (yyparse() == 0) {
        print_ast(root, 0);
    } else {
        printf("Parsing failed.\n");
    }

    fclose(file);
    free_ast(root);

    return EXIT_SUCCESS;
}
