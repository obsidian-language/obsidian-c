#include "include/ast.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Exprs
Expr *newFloatNode(double value) {
  Expr *node = malloc(sizeof(Expr));
  if (node == NULL) {
    fputs("malloc failed for float number!", stderr);
  }

  *node = (Expr){.kind = FLOAT, .u.numberFloat = {.value = value}};

  return node;
}

Expr *newIntNode(int value) {
  Expr *node = malloc(sizeof(Expr));
  if (node == NULL) {
    fputs("malloc failed for int number!", stderr);
  }

  *node = (Expr){.kind = INT, .u.numberInt = {.value = value}};

  return node;
}

Expr *newBinaryNode(char op, Expr *lhs, Expr *rhs) {
  Expr *node = malloc(sizeof(Expr));
  if (node == NULL) {
    fputs("malloc failed for float number!", stderr);
  }

  *node =
      (Expr){.kind = BINARY, .u.binary = {.op = op, .lhs = lhs, .rhs = rhs}};

  return node;
}

Expr *newUnaryNode(char op, Expr *rhs) {
  Expr *node = malloc(sizeof(Expr));
  if (node == NULL) {
    fputs("malloc failed for int number!", stderr);
  }

  *node = (Expr){.kind = UNARY, .u.unary = {.op = op, .rhs = rhs}};

  return node;
}

Expr *newGroupNode(Expr *rhs) {
  Expr *node = malloc(sizeof(Expr));
  if (node == NULL) {
    fputs("malloc failed for int number!", stderr);
  }

  *node = (Expr){.kind = GROUP, .u.group = {.rhs = rhs}};

  return node;
}

// Stmts
void initNodeStmtArray(NodeStmtArray *arr) {
  arr->size = 0;
  arr->cap = 8;
  arr->items = malloc(sizeof(Stmt *) * arr->cap);
}

void pushNodeStmt(NodeStmtArray *arr, Stmt *stmt) {
  if (arr->size >= arr->cap) {
    arr->cap *= 2;
    arr->items = realloc(arr->items, sizeof(Stmt *) * arr->cap);
    if (arr->items == NULL)
      fputs("Failed to allocate memory for NodeStmtArray\n", stderr);
  }
  arr->items[arr->size++] = stmt;
}

void freeNodeStmtArray(NodeStmtArray *arr) {
  free(arr->items);
  arr->items = NULL;
  arr->size = 0;
  arr->cap = 0;
}

Stmt *newProgramNode(NodeStmtArray *body) {
  Stmt *node = malloc(sizeof(Stmt));
  if (node == NULL) {
    fputs("malloc failed for Program Node!", stderr);
  }

  *node = (Stmt){.kind = PROGRAM, .u.program = {.body = body}};

  return node;
}

Stmt *newExprStmtNode(Expr *expr) {
  Stmt *node = malloc(sizeof(Stmt));
  if (node == NULL) {
    fputs("malloc failed for ExprStmt Node!", stderr);
  }

  *node = (Stmt){.kind = EXPRSTMT, .u.ExprStmt = {.expr = expr}};

  return node;
}

// Debugging
void debugPrintExpr(Expr *expr) {
  if (!expr) {
    printf("NULL Expression\n");
    return;
  }

  switch (expr->kind) {
  case INT:
    printf("INT: %d\n", expr->u.numberInt.value);
    break;
  case FLOAT:
    printf("FLOAT: %f\n", expr->u.numberFloat.value);
    break;
  case BINARY:
    printf("BINARY: %c\n", expr->u.binary.op);
    printf("  Left operand: ");
    debugPrintExpr(expr->u.binary.lhs);
    printf("  Right operand: ");
    debugPrintExpr(expr->u.binary.rhs);
    break;
  case UNARY:
    printf("UNARY: %c\n", expr->u.unary.op);
    printf("  Operand: ");
    debugPrintExpr(expr->u.unary.rhs);
    break;
  case GROUP:
    printf("GROUP: ");
    debugPrintExpr(expr->u.group.rhs);
    break;
  default:
    printf("Unknown Expression Type\n");
  }
}

void debugPrintStmt(Stmt *stmt) {
  if (!stmt) {
    printf("NULL Statement\n");
    return;
  }

  switch (stmt->kind) {
  case PROGRAM:
    printf("PROGRAM Statement\n");
    for (size_t i = 0; i < stmt->u.program.body->size; i++) {
      Stmt *st = stmt->u.program.body->items[i];
      debugPrintStmt(st);
    }
    break;
  case EXPRSTMT:
    printf("Expression Statement:\n");
    debugPrintExpr(stmt->u.ExprStmt.expr);
    break;
  default:
    printf("Unknown Statement Type\n");
  }
}
