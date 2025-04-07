#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include <stdbool.h>

typedef struct {
  Token *tokens;
  size_t size;
  size_t cap;
} TokenArray;

void initTokenArray(TokenArray *arr);
void appendToken(TokenArray *arr, Token token);
void freeToken(TokenArray *arr);

typedef enum {
  defaultValue = 0,
  comma = 1,           // ,
  assignment = 2,      // = += -= ...
  ternary = 3,         // ? :
  logicalOr = 4,       // ||
  logicalAnd = 5,      // &&
  bitwiseOr = 6,       // |
  bitwiseXOr = 7,      // ^
  bitwiseAnd = 8,      // &
  relational = 9,      // == !=
  comparison = 10,     //  < > <= >=
  bitShift = 11,       // << >>
  additive = 12,       // + -
  multiplicative = 13, // * / %
  prefix = 14,         // ++ -- (+ -)Unary ! ~ (type) * & sizeof
  postfix = 15,        // ++ -- () [] . -> (type){list}
} BindingPower;

typedef struct {
  TokenArray tka;
  size_t pos;
} Parser;

bool hadTokens(Parser *psr);
Token current(Parser *psr);
Token advance(Parser *psr);
Token peek(Parser *psr, int offset);

Parser *initParser(TokenArray tka);
Stmt *parse(TokenArray tka);
Expr *parseExpr(Parser *psr, BindingPower bp);
Stmt *parseStmt(Parser *psr);

// Look Table
Expr *nud(Parser *psr);
Expr *led(Parser *psr, Expr *left, BindingPower bp);
BindingPower getBp(TokenKind kind);

// Nud functions (Nothing to the left of it)
Expr *primary(Parser *psr);
Expr *unary(Parser *psr);
Expr *grouping(Parser *psr);

// Led Functions (Anything to the left)
Expr *binary(Parser *psr, Expr *left, BindingPower bp);

// Stmt lookup
Stmt *exprStmt(Parser *psr);

#endif // parser.h
