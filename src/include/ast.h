#ifndef AST_H
#define AST_H

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
    NODE_VAR_DECL
} NodeType;

typedef struct ASTNode {
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
            struct ASTNode *left;
            struct ASTNode *right;
        } binary;
        struct {
            const char *op;
            struct ASTNode *operand;
        } unary;
        struct {
            char *func_name;
            struct ASTNode **args;
            int arg_count;
        } function_call;
        struct {
            struct ASTNode **statements;
            int count;
        } statement_list;
        struct {
            char *name;
            char *type;
            struct ASTNode *value;
        } var_decl;
    };
} ASTNode;

ASTNode *create_int_node(int value);
ASTNode *create_float_node(double value);
ASTNode *create_bool_node(int value);
ASTNode *create_char_node(char value);
ASTNode *create_string_node(char *value);
ASTNode *create_identifier_node(char *name);
ASTNode *create_binary_node(const char *op, ASTNode *left, ASTNode *right);
ASTNode *create_unary_node(const char *op, ASTNode *operand);
ASTNode *create_function_call_node(char *func_name, ASTNode **args, int arg_count);
ASTNode *create_statement_list_node(ASTNode **statements, int count);
ASTNode *create_var_decl_node(char *name, char *type, ASTNode *value);
void free_ast(ASTNode *node);
void print_ast(ASTNode *node, int indent);
void print_indent(int indent);

#endif // AST_H
