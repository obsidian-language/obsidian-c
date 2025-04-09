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
        } functionDef;
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
        } whileStmt;
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
void add_param_to_list(ASTNode *list, ASTNode *param);
void free_ast(ASTNode *node);
void print_ast(ASTNode *node, int indent);
void print_indent(int indent);

#endif // AST_H
