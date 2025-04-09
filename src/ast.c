#include <stddef.h>
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

ASTNode *create_statement_list_node(ASTNode **statements, size_t count) {
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

ASTNode* create_if_statement_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_IF_STATEMENT;
    node->if_stmt.condition = condition;
    node->if_stmt.then_branch = then_branch;
    node->if_stmt.else_branch = else_branch;
    return node;
}

ASTNode* create_variable_node(const char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NODE_VAR;
    node->variable.name = strdup(name);
    return node;
}

ASTNode *create_assignment_node(char *var_name, ASTNode *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGNMENT;
    node->assignment.var_name = strdup(var_name);
    node->assignment.value = value;
    return node;
}

ASTNode *create_function_decl_node(char *name, char *return_type, char **param_names, char **param_types, int param_count, ASTNode *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_FUNCTION_DEF;
    node->function_def.name = strdup(name);
    node->function_def.return_type = strdup(return_type);
    node->function_def.param_names = param_names;
    node->function_def.param_types = param_types;
    node->function_def.param_count = param_count;
    node->function_def.body = body;
    return node;
}

ASTNode *create_param_node(char *name, char *type) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_PARAM;
    node->param.name = strdup(name);
    node->param.type = strdup(type);
    return node;
}

ASTNode *create_param_list() {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_PARAM_LIST;
    node->param_list.params = NULL;
    node->param_list.count = 0;
    return node;
}

void add_param_to_list(ASTNode *list, ASTNode *param) {
    if (list->type != NODE_PARAM_LIST) {
        fprintf(stderr, "Error: Trying to add parameter to a non-param list node.\n");
        return;
    }
    list->param_list.params = realloc(list->param_list.params, sizeof(ASTNode *) * (size_t)(list->param_list.count + 1));
    list->param_list.params[list->param_list.count++] = param;
}

ASTNode *create_while_node(ASTNode *condition, ASTNode *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_WHILE;
    node->while_stmt.condition = condition;
    node->while_stmt.body = body;
    return node;
}

ASTNode *create_println_node(ASTNode *expr) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_PRINTLN;
    node->println.expr = expr;
    return node;
}

ASTNode *create_return_node(ASTNode *expr) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_RETURN_STMT;
    node->return_stmt.expr = expr;
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
            for (size_t i = 0; i < node->statement_list.count; ++i) {
                free_ast(node->statement_list.statements[i]);
            }
            free(node->statement_list.statements);
            break;
        case NODE_VAR_DECL:
            free(node->var_decl.name);
            free(node->var_decl.type);
            free_ast(node->var_decl.value);
            break;
        case NODE_ASSIGNMENT:
            free(node->assignment.var_name);
            free_ast(node->assignment.value);
            break;
        case NODE_IF_STATEMENT:
            free_ast(node->if_stmt.condition);
            free_ast(node->if_stmt.then_branch);
            free_ast(node->if_stmt.else_branch);
            break;
        case NODE_VAR:
            free(node->variable.name);
            break;
        case NODE_FUNCTION_DEF:
            free(node->function_def.name);
            free(node->function_def.return_type);
            for (int i = 0; i < node->function_def.param_count; ++i) {
                free(node->function_def.param_names[i]);
                free(node->function_def.param_types[i]);
            }
            free(node->function_def.param_names);
            free(node->function_def.param_types);
            free_ast(node->function_def.body);
            break;
        case NODE_PARAM:
            free(node->param.name);
            free(node->param.type);
            break;
        case NODE_PARAM_LIST:
            for (int i = 0; i < node->param_list.count; ++i) {
                free_ast(node->param_list.params[i]);
            }
            free(node->param_list.params);
            break;
        case NODE_WHILE:
            free_ast(node->while_stmt.condition);
            free_ast(node->while_stmt.body);
            break;
        case NODE_PRINTLN:
            free_ast(node->println.expr);
            break;
        case NODE_RETURN_STMT:
            free_ast(node->return_stmt.expr);
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
            for (size_t i = 0; i < node->statement_list.count; ++i) {
                print_ast(node->statement_list.statements[i], indent + 1);
            }
            break;
        case NODE_VAR:
            printf("Variable: %s\n", node->variable.name);
            break;
        case NODE_VAR_DECL:
            printf("VarDecl: name=%s, type=%s\n", node->var_decl.name, node->var_decl.type);
            print_ast(node->var_decl.value, indent + 1);
            break;
        case NODE_IF_STATEMENT:
            printf("IfStatement:\n");
            print_indent(indent + 1);
            printf("Condition:\n");
            print_ast(node->if_stmt.condition, indent + 2);
            print_indent(indent + 1);
            printf("ThenBranch:\n");
            print_ast(node->if_stmt.then_branch, indent + 2);
            if (node->if_stmt.else_branch) {
                print_indent(indent + 1);
                printf("ElseBranch:\n");
                print_ast(node->if_stmt.else_branch, indent + 2);
            }
            break;
        case NODE_ASSIGNMENT:
            printf("Assignment: %s\n", node->assignment.var_name);
            print_ast(node->assignment.value, indent + 1);
            break;
        case NODE_FUNCTION_DEF:
            printf("function_def: %s\n", node->function_def.name);
            print_indent(indent + 1);
            printf("Return Type: %s\n", node->function_def.return_type);
            print_indent(indent + 1);
            printf("Parameters:\n");
            for (int i = 0; i < node->function_def.param_count; ++i) {
                print_indent(indent + 1);
                printf("  Param %d: %s %s\n", i + 1, node->function_def.param_types[i], node->function_def.param_names[i]);
            }
            print_indent(indent + 1);
            printf("Body:\n");
            print_ast(node->function_def.body, indent + 1);
            break;
        case NODE_PARAM_LIST:
            printf("ParamList:\n");
            for (int i = 0; i < node->param_list.count; ++i) {
                print_indent(indent + 1);
                print_ast(node->param_list.params[i], indent + 1);
            }
            break;
        case NODE_PARAM:
            print_indent(indent + 1);
            printf("Param: %s %s\n", node->param.type, node->param.name);
            break;
        case NODE_WHILE:
            printf("WhileStatement:\n");
            print_indent(indent + 1);
            printf("Condition:\n");
            print_ast(node->while_stmt.condition, indent + 2);
            print_indent(indent + 1);
            printf("Body:\n");
            print_ast(node->while_stmt.body, indent + 1);
            break;
        case NODE_PRINTLN:
            printf("PrintLn:\n");
            print_indent(indent + 1);
            printf("Value:\n");
            print_ast(node->println.expr, indent + 2);
            break;
        case NODE_RETURN_STMT:
            printf("Return:\n");
            print_indent(indent + 1);
            printf("Value:\n");
            print_ast(node->return_stmt.expr, indent + 2);
            break;
        default:
            print_indent(indent);
            printf("Unknown node type!\n");
    }
}
