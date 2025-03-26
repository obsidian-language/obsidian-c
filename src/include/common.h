#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

#define MAJOR_VERSION 0
#define MINOR_VERSION 1
#define PATCH_VERSION 0

void printHelpMenu(void);
void printVersion(void);
void printOptimizersHelp(void);
void printTargetHelp(void);
void printWarningsHelp(void);
void systemInfo(char *output, size_t size);

// Redefined when #include <string.h>
// char *strdup(const char *s);

#endif // COMMON_H
