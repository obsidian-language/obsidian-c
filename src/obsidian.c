/**
 * @file obsidian.c
 * @brief Main entry point for the Obsidian compiler.
 *
 * This file contains the main function and initialization logic for the 
 * Obsidian compiler. It handles command-line arguments, sets up the 
 * environment, and starts the compilation process.
 * 
 * @author Codezz-ops <codezz-ops@obsidian.cc>
 * 
 * @copyright Copyright (c) 2024 Obsidian Language
 * @license BSD 3-Clause
 */

#ifdef _WIN32
// Silence deprecation warnings on Windows
#define _CRT_SECURE_NO_WARNINGS
#endif // WIN32

#include "include/common.h"
#include "include/lexer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The main entry point of the Obsidian compiler.
 * 
 * This function processes command-line arguments, opens the input file,
 * reads its contents into memory, initializes the lexer, and retrieves
 * tokens from the source code until the end of the file is reached.
 * 
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return int Returns EXIT_SUCCESS on successful execution, or EXIT_FAILURE on error.
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fputs("obsidian: error: no input file\n", stderr);
        return EXIT_FAILURE;
    }

    long length;
    FILE *file;
    char *buffer;
    Lexer lexer;
    size_t bytesRead;

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
     
    file = fopen(argv[1], "r");
    if (file == NULL) {
        fputs("obsidian: error: could not read file\n", stderr);
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    rewind(file);

    buffer = (char *)malloc((size_t)(length + 1));
    if (buffer == NULL) {
        fprintf(stderr, "obsidian: error: could not allocate memory for file '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    bytesRead = fread(buffer, 1, (size_t)(length), file);
    if (bytesRead != (size_t)length) {
        fprintf(stderr, "obsidian: error: could not read file '%s'\n", argv[1]);
        free(buffer);
        fclose(file);
        return EXIT_FAILURE;
    }
    buffer[length] = '\0';

    initLexer(&lexer, buffer);

    while (1) {
        Token token = getNextToken(&lexer);
        if (token.type == TEof) {
            break;
        }

        printf("Token: %d\n", token.type);
    }

    fclose(file);
    free(buffer);

    return EXIT_SUCCESS;
}
