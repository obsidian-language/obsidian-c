#ifndef AST_H
#define AST_H

#include <stddef.h>
typedef enum { PROGRAM, FLOAT, INT, BINARY, UNARY, GROUP, EXPRSTMT } NodeKind;

typedef struct Expr Expr;
typedef struct Stmt Stmt;

struct Expr {
  NodeKind kind;

  union {
    struct {
      int value;
    } numberInt;
    struct {
      double value;
    } numberFloat;
    struct {
      char op;
      Expr *lhs;
      Expr *rhs;
    } binary;
    struct {
      char op;
      Expr *rhs;
    } unary;
    struct {
      Expr *rhs;
    } group;
  } u;
};

Expr *newFloatNode(double value);
Expr *newIntNode(int value);
Expr *newBinaryNode(char op, Expr *lhs, Expr *rhs);
Expr *newUnaryNode(char op, Expr *rhs);
Expr *newGroupNode(Expr *rhs);

void debugPrintExpr(Expr *expr);

typedef struct {
  Stmt **items;
  size_t size;
  size_t cap;
} NodeStmtArray;

void initNodeStmtArray(NodeStmtArray *arr);
void pushNodeStmt(NodeStmtArray *arr, Stmt *stmt);
void freeNodeStmtArray(NodeStmtArray *arr);

struct Stmt {
  NodeKind kind;

  union {
    struct {
      NodeStmtArray *body;
    } program;
    struct {
      Expr *expr;
    } ExprStmt;
  } u;
};

Stmt *newProgramNode(NodeStmtArray *body);
Stmt *newExprStmtNode(Expr *expr);

void debugPrintStmt(Stmt *stmt);

#endif // AST_H
