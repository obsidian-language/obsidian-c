#include "include/parser.h"
#include "include/ast.h"
#include "include/error.h"
#include "include/lexer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initTokenArray(TokenArray *arr) {
  arr->size = 0;
  arr->cap = 8;
  arr->tokens = malloc(sizeof(Token) * arr->cap);
}

void appendToken(TokenArray *arr, Token token) {
  if (arr->size >= arr->cap) {
    arr->cap *= 2;
    arr->tokens = realloc(arr->tokens, sizeof(Token) * arr->cap);
    if (arr->tokens == NULL) {
      fputs("Memory alloction error", stderr);
    }
  }

  arr->tokens[arr->size++] = token;
}

void freeToken(TokenArray *arr) { free(arr->tokens); }

Parser *initParser(TokenArray tka) {
  Parser *p = malloc(sizeof(Parser));
  if (p == NULL)
    return NULL;

  p->tka = tka;
  p->pos = 0;

  return p;
}

bool hadTokens(Parser *psr) { return psr->pos < psr->tka.size; }
Token current(Parser *psr) { return psr->tka.tokens[psr->pos]; }
Token advance(Parser *psr) { return psr->tka.tokens[psr->pos++]; }
Token peek(Parser *psr, int offset) {
  return psr->tka.tokens[psr->pos + (size_t)offset];
}

BindingPower getBp(TokenKind kind) {
  switch (kind) {
  case TPlus:
  case TMinus:
    return additive;
  case TStar:
  case TSlash:
    return multiplicative;
  default:
    return defaultValue;
  }
}

Expr *nud(Parser *psr) {
  switch (current(psr).type) {
  case TIntLiteral:
  case TFloatLiteral:
  case TIdentifier:
  case TStringLiteral:
  case TCharLiteral:
    return primary(psr);
  case TMinus:
    return unary(psr);
  case TLparen:
    return grouping(psr);
  default:
    advance(psr);
    return NULL;
  }
}

Expr *led(Parser *psr, Expr *left, BindingPower bp) {
  switch (current(psr).type) {
  case TPlus:
  case TMinus:
  case TStar:
  case TSlash:
    return binary(psr, left, bp);
  default:
    advance(psr);
    return left;
  }
}

Stmt *parse(TokenArray tka) {
  Parser *p = initParser(tka);

  NodeStmtArray body;
  initNodeStmtArray(&body);

  while (hadTokens(p)) {
    if (current(p).type == TEof)
      break;
    pushNodeStmt(&body, parseStmt(p));
  }

  Stmt *program = newProgramNode(&body);

  free(p);
  freeNodeStmtArray(&body);
  return program;
}

Stmt *parseStmt(Parser *psr) {
  switch (current(psr).type) {
  default:
    return exprStmt(psr);
  }
}

Stmt *exprStmt(Parser *psr) {
  Expr *expr = parseExpr(psr, defaultValue);
  return newExprStmtNode(expr);
}

Expr *parseExpr(Parser *psr, BindingPower bp) {
  Expr *lhs = nud(psr);
  if (lhs == NULL)
    return lhs;

  BindingPower cbp = getBp(current(psr).type);
  while (cbp > bp) {
    lhs = led(psr, lhs, cbp);
  }

  return lhs;
}

Expr *primary(Parser *psr) {
  switch (current(psr).type) {
  case TIntLiteral:
    return newIntNode(atoi(advance(psr).start));
  case TFloatLiteral:
    return newFloatNode(atof(advance(psr).start));
  default:
    error(SemanticError, "Could not parser current token ",
          (Token *)current(psr).start);
    return NULL;
  }
}

Expr *unary(Parser *psr) {
  Token op = advance(psr);
  Expr *rhs = parseExpr(psr, defaultValue);
  return newUnaryNode(*op.start, rhs);
}

Expr *binary(Parser *psr, Expr *left, BindingPower bp) {
  Token op = advance(psr);
  Expr *right = parseExpr(psr, bp);
  return newBinaryNode(*op.start, left, right);
}

Expr *grouping(Parser *psr) {
  advance(psr); // consume the (
  Expr *expr = parseExpr(psr, defaultValue);
  advance(psr); // consume the )
  return newGroupNode(expr);
}
