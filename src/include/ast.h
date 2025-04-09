#ifndef AST_H
#define AST_H

#include <stddef.h>
typedef enum {
    NODE_INT_LITERAL,
    NODE_FLOAT_LITERAL,
    NODE_BOOL_LITERAL,
    NODE_CHAR_LITERAL,
    NODE_STRING_LITERAL,
    NODE_IDENTIFIER,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_FUNCTION_CALL,
    NODE_STATEMENT_LIST,
    NODE_DECLARATION,
    NODE_FUNCTION_DEF,
    NODE_RETURN_STMT,
    NODE_VAR_DECL,
    NODE_IF_STATEMENT,
    NODE_VAR,
    NODE_ASSIGNMENT,
    NODE_PARAM,
    NODE_PARAM_LIST,
    NODE_WHILE,
    NODE_PRINTLN,
    NODE_ARG_LIST,
    NODE_LENGTH_STMT,
    NODE_TYPEOF_STMT,
    NODE_ALLOC_STMT,
    NODE_DEALLOC_STMT,
    NODE_SIZEOF_STMT,
    NODE_UNSAFE_STMT,
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
        } binary;
        struct {
            const char *op;
            ASTNode *operand;
        } unary;
        struct {
            char *func_name;
            ASTNode **args;
            int arg_count;
        } function_call;
        struct {
            ASTNode **statements;
            size_t count;
        } statement_list;
        struct {
            char *name;
            char *type;
            ASTNode *value;
        } var_decl;
        struct {
            ASTNode* condition;
            ASTNode* then_branch;
            ASTNode* else_branch;
        } if_stmt;
        struct {
            char *name;
        } variable;
        struct {
            char *var_name;
            ASTNode *value;
        } assignment;
        struct {
            char *name;
            char *return_type;
            char **param_names;
            char **param_types;
            int param_count;
            ASTNode *body;
        } function_def;
        struct {
            char *name;
            char *type;
        } param;
        struct {
            ASTNode **params;
            int count;
        } param_list;
        struct {
            ASTNode *condition;
            ASTNode *body;
        } while_stmt;
        struct {
            ASTNode *expr;
        } println;
        struct {
            ASTNode *expr;
        } return_stmt;
        struct {
            ASTNode *expr;
        } length_stmt;
        struct {
            ASTNode *expr;
        } typeof_stmt;
        struct {
            ASTNode *size;
        } alloc_stmt;
        struct {
            ASTNode *pointer;
        } dealloc_stmt;
        struct {
            char *type;
        } sizeof_stmt;
        struct {
            ASTNode *body;
        } unsafe_stmt;
        struct {
            ASTNode **args;
            int count;
        } arg_list;
    };
};

// Function prototypes
ASTNode *create_int_node(int value);
ASTNode *create_float_node(double value);
ASTNode *create_bool_node(int value);
ASTNode *create_char_node(char value);
ASTNode *create_string_node(char *value);
ASTNode *create_identifier_node(char *name);
ASTNode *create_binary_node(const char *op, ASTNode *left, ASTNode *right);
ASTNode *create_unary_node(const char *op, ASTNode *operand);
ASTNode *create_function_call_node(char *func_name, ASTNode **args, int arg_count);
ASTNode *create_statement_list_node(ASTNode **statements, size_t count);
ASTNode *create_var_decl_node(char *name, char *type, ASTNode *value);
ASTNode *create_if_statement_node(ASTNode *condition, ASTNode *then_branch, ASTNode *else_branch);
ASTNode *create_variable_node(const char *name);
ASTNode *create_assignment_node(char *var_name, ASTNode *value);
ASTNode *create_function_decl_node(char *name, char *return_type, char **param_names, char **param_types, int param_count, ASTNode *body);
ASTNode *create_param_node(char *name, char *type);
ASTNode *create_param_list(void);
ASTNode *create_while_node(ASTNode *condition, ASTNode *body);
ASTNode *create_println_node(ASTNode *expr);
ASTNode *create_length_node(ASTNode *expr);
ASTNode *create_return_node(ASTNode *expr);
ASTNode *create_typeof_node(ASTNode *expr);
ASTNode *create_alloc_node(ASTNode *size);
ASTNode *create_dealloc_node(ASTNode *pointer);
ASTNode *create_sizeof_node(char *type);
ASTNode *create_unsafe_node(ASTNode *body);
ASTNode *create_arg_list(void);
void add_arg_to_list(ASTNode *list, ASTNode *arg);
void add_param_to_list(ASTNode *list, ASTNode *param);
void free_ast(ASTNode *node);
void print_ast(ASTNode *node, int indent);
void print_indent(int indent);

#endif // AST_H
