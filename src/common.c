#include "include/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined (_WIN32)  || defined(_WIN64)
    #include <windows.h>
#else
    #include <sys/utsname.h>
#endif

void printHelpMenu(void) {
    puts("Usage: obsidian [options] file...\n"
        "Options:\n"
        " --help           Displays this infomation.\n"
        " --help={optimizers|warnings|target}[,...].\n\n"
        " --version        Display compiler version infomation.\n\n"
        " -save-temps      Do not delete intermediate files.\n\n"
        " -S               Compile only; do not assemble or link.\n"
        " -c               Compile and assemble, but do not link.\n"
        " -o <file>        Place the output into <file>.\n\n"
        "Report bugs at <https://github.com/obsidian-language/obsidian/issues>");
}

void printOptimizersHelp(void) {
    puts("The following options contorl optimizations:\n"
            " -O<number>        Set optimization level to <number>\n");
}

void printTargetHelp(void) {
    puts("The following options are target specific:\n");
}

void printWarningsHelp(void) {
    puts("The following options control compiler warning messages:\n");
}

void printVersion(void) {
    char os_name[128];
    systemInfo(os_name, sizeof(os_name));
    printf("obsidian version %d.%d.%d (%s %d.%d.%d)\n", MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION, os_name, MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION);
}

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
        strncpy(output, "Unknown", size - 1);
    } else {
        strncpy(output, buffer.sysname, size - 1);
    }
#endif

    output[size - 1] = '\0';
}

char *strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *copy = (char *)malloc(len);
    if (copy) {
        memcpy(copy, s, len);
    }
    return copy;
}
