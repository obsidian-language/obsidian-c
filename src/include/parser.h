#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    NODE_BINARY,
    NODE_LITERAL,
    NODE_IDENTIFIER
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        struct {
            struct ASTNode *left;
            TokenKind op;
            struct ASTNode *right;
        } binary;
        int intValue;
        float floatValue;
        char *identifier;
    };
} ASTNode;

typedef struct {
    Lexer *lexer;
    Token current;
} Parser;

void initParser(Parser *parser, Lexer *lexer);
ASTNode *parseExpression(Parser *parser);
ASTNode *parseTerm(Parser *parser);
ASTNode *parsePrimary(Parser *parser);
ASTNode *createBinaryNode(ASTNode *left, TokenKind op, ASTNode *right);
ASTNode *createLiteralNode(int value);
ASTNode *createIdentifierNode(char *identifier);
void advance(Parser *parser);
int match(Parser *parser, TokenKind type);
void freeAST(ASTNode *node);
void printAST(ASTNode *node, int depth);

#endif // PARSER_H
