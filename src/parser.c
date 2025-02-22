#include "include/parser.h"
#include <stdlib.h>
#include <stdio.h>

void initParser(Parser *parser, Lexer *lexer) {
    parser->lexer = lexer;
    parser->current = getNextToken(lexer);
}

void advance(Parser *parser) {
    parser->current = getNextToken(parser->lexer);
}

int match(Parser *parser, TokenKind type) {
    if (parser->current.type == type) {
        advance(parser);
        return 1;
    }
    return 0;
}

ASTNode *createBinaryNode(ASTNode *left, TokenKind op, ASTNode *right) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_BINARY;
    node->binary.left = left;
    node->binary.op = op;
    node->binary.right = right;
    return node;
}

ASTNode *createLiteralNode(int value) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_LITERAL;
    node->intValue = value;
    return node;
}

ASTNode *createIdentifierNode(char *identifier) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = NODE_IDENTIFIER;
    node->identifier = identifier;
    return node;
}

ASTNode *parseIdentifier(Parser *parser) {
    if (parser->current.type == TIdentifier) {
        ASTNode *node = createIdentifierNode(parser->current.start);
        advance(parser);
        return node;
    }

    printf("Error: Expected identifier\n");
    exit(1);
}

ASTNode *parsePrimary(Parser *parser) {
    if (parser->current.type == TIntLiteral) {
        ASTNode *node = createLiteralNode(atoi(parser->current.start));
        advance(parser);
        return node;
    }

    if (parser->current.type == TIdentifier) {
        return parseIdentifier(parser);
    }

    if (parser->current.type == TLparen) {
        advance(parser);
        ASTNode *expr = parseExpression(parser);
        if (parser->current.type != TRparen) {
            printf("Error: Expected closing ')'\n");
            exit(1);
        }
        advance(parser);
        return expr;
    }

    printf("Error: Expected literal or identifier\n");
    exit(1);
}

ASTNode *parseTerm(Parser *parser) {
    ASTNode *node = parsePrimary(parser);

    while (parser->current.type == TStar || parser->current.type == TSlash) {
        TokenKind op = parser->current.type;
        advance(parser);
        node = createBinaryNode(node, op, parsePrimary(parser));
    }

    return node;
}

ASTNode *parseExpression(Parser *parser) {
    ASTNode *node = parseTerm(parser);

    while (parser->current.type == TPlus || parser->current.type == TMinus) {
        TokenKind op = parser->current.type;
        advance(parser);
        node = createBinaryNode(node, op, parseTerm(parser));
    }

    return node;
}

void freeAST(ASTNode *node) {
    if (!node) return;
    if (node->type == NODE_BINARY) {
        freeAST(node->binary.left);
        freeAST(node->binary.right);
    }
    free(node);
}

void printAST(ASTNode *node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    switch (node->type) {
        case NODE_BINARY:
            printf("Binary: %d\n", node->binary.op);
            printAST(node->binary.left, depth + 1);
            printAST(node->binary.right, depth + 1);
            break;
        case NODE_LITERAL:
            printf("Literal: %d\n", node->intValue);
            break;
        case NODE_IDENTIFIER:
            printf("Identifier: %s\n", node->identifier);
            break;
    }
}