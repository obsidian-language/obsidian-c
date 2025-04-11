#ifndef AST_H
#define AST_H

#include <stddef.h>

typedef enum {
    NODE_PARAM,
    NODE_PARAM_LIST,
    NODE_ARG_LIST,

    NodeIntLitExpr,
    NodeFloatLitExpr,
    NodeBoolLitExpr,
    NodeCharLitExpr,
    NodeStringLitExpr,
    NodeIdentiferExpr,
    NodeBinaryExpr,
    NodeUnaryExpr,
    NodeVarExpr,
    NodeAssignmentExpr,
    NodePrintLnExpr,
    NodeLengthExpr,
    NodeTypeOfExpr,
    NodeAllocExpr,
    NodeDeallocExpr,
    NodeSizeOfExpr,
    NodeUnsafeExpr,
    NodeCastExpr,

    NodeFunctionCallStmt,
    NodeBlockStmt,
    NodeFunctionDefStmt,
    NodeReturnStmt,
    NodeVarDeclStmt,
    NodeIfStmt,
    NodeWhileStmt,
    NodeForStmt,
} NodeType;

typedef struct ASTNode ASTNode;

struct ASTNode {
    NodeType type;
    char *typeStr;

    union {
        int intval;
        double floatval;
        int boolval;
        char charval;
        char *strval;
        struct {
            const char *op;
            ASTNode *left;
            ASTNode *right;
        } binary_expr;
        struct {
            const char *op;
            ASTNode *operand;
        } unary_expr;
        struct {
            char *var_name;
            ASTNode *value;
        } assignment_expr;
        struct {
            ASTNode *expr;
        } println_expr;
        struct {
            ASTNode *expr;
        } length_expr;
        struct {
            ASTNode *expr;
        } typeof_expr;
        struct {
            ASTNode *size;
        } alloc_expr;
        struct {
            ASTNode *pointer;
        } dealloc_expr;
        struct {
            char *type;
        } sizeof_expr;
        struct {
            ASTNode *body;
        } unsafe_expr;
        struct {
            ASTNode *expr;
            char *type;
        } cast_expr;
        struct {
            char *name;
        } variable;
        struct {
            ASTNode **statements;
            size_t count;
        } statement_list;
        struct {
            ASTNode *expr;
        } return_stmt;
        struct {
            ASTNode *condition;
            ASTNode *body;
        } while_stmt;
        struct {
            ASTNode *condition;
            ASTNode *then_branch;
            ASTNode *else_branch;
        } if_stmt;
        struct {
            char *func_name;
            ASTNode **args;
            int arg_count;
        } function_call_stmt;
        struct {
            char *name;
            char *return_type;
            char **param_names;
            char **param_types;
            int param_count;
            ASTNode *body;
        } function_def_stmt;
        struct {
            char *name;
            char *type;
            ASTNode *value;
        } var_decl_stmt;
        struct {
            ASTNode *init;
            ASTNode *condition;
            ASTNode *increment;
            ASTNode *body;
        } for_loop_stmt;
        struct {
            char *name;
            char *type;
        } param;
        struct {
            ASTNode **params;
            int count;
        } param_list;
        struct {
            ASTNode **args;
            int count;
        } arg_list;
    };
};

ASTNode *create_int_node(int value);
ASTNode *create_float_node(double value);
ASTNode *create_bool_node(int value);
ASTNode *create_char_node(char value);
ASTNode *create_string_node(char *value);
ASTNode *create_identifier_node(char *name);
ASTNode *create_binary_node(const char *op, ASTNode *left, ASTNode *right);
ASTNode *create_unary_node(const char *op, ASTNode *operand);
ASTNode *create_variable_node(const char *name);
ASTNode *create_assignment_node(char *var_name, ASTNode *value);
ASTNode *create_println_node(ASTNode *expr);
ASTNode *create_length_node(ASTNode *expr);
ASTNode *create_typeof_node(ASTNode *expr);
ASTNode *create_alloc_node(ASTNode *size);
ASTNode *create_dealloc_node(ASTNode *pointer);
ASTNode *create_sizeof_node(char *type);
ASTNode *create_unsafe_node(ASTNode *body);
ASTNode *create_return_node(ASTNode *expr);
ASTNode *create_while_node(ASTNode *condition, ASTNode *body);
ASTNode *create_if_statement_node(ASTNode *condition, ASTNode *then_branch, ASTNode *else_branch);
ASTNode *create_statement_list_node(ASTNode **statements, size_t count);
ASTNode *create_function_call_node(char *func_name, ASTNode **args, int arg_count);
ASTNode *create_function_decl_node(char *name, char *return_type, char **param_names, char **param_types, int param_count, ASTNode *body);
ASTNode *create_var_decl_node(char *name, char *type, ASTNode *value);
ASTNode* create_for_node(ASTNode* init, ASTNode* condition, ASTNode* increment, ASTNode* body);
ASTNode *create_param_node(char *name, char *type);
ASTNode *create_cast_node(ASTNode *expr, char *type);
ASTNode *create_param_list(void);
ASTNode *create_arg_list(void);
void add_arg_to_list(ASTNode *list, ASTNode *arg);
void add_param_to_list(ASTNode *list, ASTNode *param);
void print_ast_inline(ASTNode *node);
void print_ast(ASTNode *node, int indent);
void print_indent(int indent);
void free_ast(ASTNode *node);

#endif // AST_H
