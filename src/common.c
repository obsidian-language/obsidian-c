/**
 * @file common.c
 * @brief Implements common utility functions for the Obsidian programming language.
 *
 * This file contains utility functions and definitions that are used across 
 * different modules of the Obsidian compiler. It provides shared functionality 
 * to facilitate code reuse and maintainability.
 * 
 * @author Codezz-ops <codezz-ops@obsidian.cc>
 * 
 * @copyright Copyright (c) 2024 Obsidian Language
 * @license BSD 3-Clause
 */

#include "include/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined (_WIN32)  || defined(_WIN64)
    #include <windows.h>
#else
    #include <sys/utsname.h>
#endif

/**
 * @brief Displays the help menu for the Obsidian compiler.
 * 
 * This function prints the usage information, including available options
 * and their descriptions, to the standard output.
 */
void printHelpMenu(void) {
    puts("Usage: obsidian [options] file...\n"
        "Options:\n"
        " --help           Displays this information.\n"
        " --help={optimizers|warnings|target}[,...].\n\n"
        " --version        Display compiler version information.\n\n"
        " -save-temps      Do not delete intermediate files.\n\n"
        " -S               Compile only; do not assemble or link.\n"
        " -c               Compile and assemble, but do not link.\n"
        " -o <file>        Place the output into <file>.\n\n"
        "Report bugs at <https://github.com/obsidian-language/obsidian/issues>");
}

/**
 * @brief Displays help information for optimization options.
 * 
 * This function prints the available optimization options and their
 * descriptions to the standard output.
 */
void printOptimizersHelp(void) {
    puts("The following options control optimizations:\n"
            " -O<number>        Set optimization level to <number>\n");
}

/**
 * @brief Displays help information for target-specific options.
 * 
 * This function prints the available target-specific options and their
 * descriptions to the standard output.
 */
void printTargetHelp(void) {
    puts("The following options are target specific:\n");
}

/**
 * @brief Displays help information for compiler warning messages.
 * 
 * This function prints the available options for controlling compiler
 * warning messages to the standard output.
 */
void printWarningsHelp(void) {
    puts("The following options control compiler warning messages:\n");
}

/**
 * @brief Prints the version information of the Obsidian compiler.
 * 
 * This function retrieves the system information and prints the current
 * version of the Obsidian compiler to the standard output.
 */
void printVersion(void) {
    char os_name[128];
    systemInfo(os_name, sizeof(os_name));
    printf("obsidian version %d.%d.%d (%s %d.%d.%d)\n", MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION, os_name, MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION);
}

/**
 * @brief Retrieves the system information and stores it in the provided output buffer.
 * 
 * @param output Pointer to the buffer where the system name will be stored.
 * @param size Size of the output buffer.
 * 
 * This function checks the operating system and retrieves its name,
 * storing it in the provided output buffer. If the buffer is invalid
 * or if an error occurs, an appropriate message is printed to stderr.
 */
void systemInfo(char *output, size_t size) {
#if defined(_WIN32) || defined(_WIN64)
    int copy_status;
#else
    struct utsname buffer;
#endif

    if (output == NULL || size == 0) {
        fprintf(stderr, "Invalid output buffer or size\n");
        return;
    }

#if defined(_WIN32) || defined(_WIN64)
    copy_status = strcpy_s(output, size, "Windows");
    if (copy_status != 0) {
        fprintf(stderr, "Failed to copy system name\n");
    }
#else
    if (uname(&buffer) != 0) {
        perror("uname");
        snprintf(output, size, "%s", "Unknown");
    } else {
        snprintf(output, size,"%s", buffer.sysname); 
    }
#endif

    output[size - 1] = '\0';
}
