#ifndef AST_H
#define AST_H

#include <stddef.h>
typedef enum {
  PROGRAM,
  FLOAT,
  INT,
  STRING,
  CHAR,
  IDENT,
  BINARY,
  UNARY,
  GROUP,
  EXPRSTMT,
  VARSTMT
} NodeKind;

typedef enum {
  PRIMITIVE, // int, char, ...
  NAMED,     // user defined
} TypeKind;

typedef struct Expr Expr;
typedef struct Stmt Stmt;
typedef struct Type Type;

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
      const char *value;
    } string;
    struct {
      char value;
    } _char;
    struct {
      const char *value;
    } ident;
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
Expr *newStringNode(const char *value);
Expr *newCharNode(char value);
Expr *newIdentNode(const char *value);
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
    struct {
      Type *type;
      const char *name;
      Expr *body;
    } VarDecl;
  } u;
};

Stmt *newProgramNode(NodeStmtArray *body);
Stmt *newExprStmtNode(Expr *expr);
Stmt *newVarDeclNode(Type *type, const char *name, Expr *body);

void debugPrintStmt(Stmt *stmt);

struct Type {
  TypeKind kind;

  union {
    struct {
      const char *type;
    } primative;
  } u;
};

Type *newPrimativeTypeNode(const char *type);

void debugPrintType(Type *type);

#endif // AST_H
