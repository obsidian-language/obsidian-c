#if defined (__linux__) || defined (__unix__) || defined (__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/ast.h"

ASTNode *create_int_node(int value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_INT_LITERAL;
    node->intval = value;
    node->typeStr = strdup("i64");
    return node;
}

ASTNode *create_float_node(double value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_FLOAT_LITERAL;
    node->floatval = value;
    node->typeStr = strdup("f64");
    return node;
}

ASTNode *create_bool_node(int value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_BOOL_LITERAL;
    node->boolval = value;
    return node;
}

ASTNode *create_char_node(char value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_CHAR_LITERAL;
    node->charval = value;
    return node;
}

ASTNode *create_string_node(char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_STRING_LITERAL;
    node->strval = strdup(value);
    return node;
}

ASTNode *create_identifier_node(char *name) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_IDENTIFIER;
    node->strval = strdup(name);
    return node;
}

ASTNode *create_binary_node(const char *op, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_BINARY_OP;
    node->binary.op = op;
    node->binary.left = left;
    node->binary.right = right;
    return node;
}

ASTNode *create_unary_node(const char *op, ASTNode *operand) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_UNARY_OP;
    node->unary.op = op;
    node->unary.operand = operand;
    return node;
}

ASTNode *create_function_call_node(char *func_name, ASTNode **args, int arg_count) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNCTION_CALL;
    node->function_call.func_name = strdup(func_name);
    node->function_call.args = args;
    node->function_call.arg_count = arg_count;
    return node;
}

ASTNode *create_statement_list_node(ASTNode **statements, int count) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_STATEMENT_LIST;
    node->statement_list.statements = statements;
    node->statement_list.count = count;
    return node;
}

ASTNode *create_var_decl_node(char *name, char *type, ASTNode *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_VAR_DECL;
    node->var_decl.name = strdup(name);
    node->var_decl.type = strdup(type);
    node->var_decl.value = value;
    node->typeStr = strdup(type);
    return node;
}

void free_ast(ASTNode *node) {
    if (node == NULL) return;

    switch (node->type) {  
        case NODE_INT_LITERAL:
        case NODE_FLOAT_LITERAL:
        case NODE_BOOL_LITERAL:
        case NODE_CHAR_LITERAL:
            break;
        case NODE_STRING_LITERAL:
            free(node->strval);
            break;
        case NODE_IDENTIFIER:
            free(node->strval);
            break;
        case NODE_BINARY_OP:
            free_ast(node->binary.left);
            free_ast(node->binary.right);
            break;
        case NODE_UNARY_OP:
            free_ast(node->unary.operand);
            break;
        case NODE_FUNCTION_CALL:
            free(node->function_call.func_name);
            for (int i = 0; i < node->function_call.arg_count; ++i) {
                free_ast(node->function_call.args[i]);
            }
            free(node->function_call.args);
            break;
        case NODE_STATEMENT_LIST:
            for (int i = 0; i < node->statement_list.count; ++i) {
                free_ast(node->statement_list.statements[i]);
            }
            free(node->statement_list.statements);
            break;
        case NODE_VAR_DECL:
            free(node->var_decl.name);
            free(node->var_decl.type);
            free_ast(node->var_decl.value);
            break;

        default:
            printf("Unknown node type, skipping free operation.\n");
            break;
    }

    free(node);
}

void print_indent(int indent) {
    for (int i = 0; i < indent; ++i)
        printf("  ");
}

void print_ast(ASTNode *node, int indent) {
    if (!node) return;

    print_indent(indent);
    switch (node->type) {
        case NODE_INT_LITERAL:
            printf("IntLiteral: %d\n", node->intval);
            break;
        case NODE_FLOAT_LITERAL:
            printf("FloatLiteral: %f\n", node->floatval);
            break;
        case NODE_BOOL_LITERAL:
            printf("BoolLiteral: %s\n", node->boolval ? "true" : "false");
            break;
        case NODE_CHAR_LITERAL:
            printf("CharLiteral: '%c'\n", node->charval);
            break;
        case NODE_STRING_LITERAL:
            printf("StringLiteral: %s\n", node->strval);
            break;
        case NODE_IDENTIFIER:
            printf("Identifier: %s\n", node->strval);
            break;
        case NODE_BINARY_OP:
            printf("BinaryOp: '%s'\n", node->binary.op);
            print_ast(node->binary.left, indent + 1);
            print_ast(node->binary.right, indent + 1);
            break;
        case NODE_UNARY_OP:
            printf("UnaryOp: '%s'\n", node->unary.op);
            print_ast(node->unary.operand, indent + 1);
            break;
        case NODE_FUNCTION_CALL:
            printf("FunctionCall: %s\n", node->function_call.func_name);
            for (int i = 0; i < node->function_call.arg_count; ++i) {
                print_ast(node->function_call.args[i], indent + 1);
            }
            break;
        case NODE_STATEMENT_LIST:
            printf("StatementList:\n");
            for (int i = 0; i < node->statement_list.count; ++i) {
                print_ast(node->statement_list.statements[i], indent + 1);
            }
            break;
        case NODE_VAR_DECL:
            printf("VarDecl: name=%s, type=%s\n", node->var_decl.name, node->var_decl.type);
            print_ast(node->var_decl.value, indent + 1);
            break;
        default:
            print_indent(indent);
            printf("Unknown node type!\n");
    }
}
