#ifndef ERROR_H
#define ERROR_H

#include "lexer.h"

typedef enum {
    LexicalError,
    SyntaxError,
    SemanticError
} ErrorType;

const char* errorTypeToString(ErrorType type);
int error(ErrorType type, const char *message, Token *token);

#endif // ERROR_H
