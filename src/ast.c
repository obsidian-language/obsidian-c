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
    node->type = NodeIntLitExpr;
    node->intval = value;
    node->typeStr = strdup("i64");
    return node;
}

ASTNode *create_float_node(double value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeFloatLitExpr;
    node->floatval = value;
    node->typeStr = strdup("f64");
    return node;
}

ASTNode *create_bool_node(int value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeBoolLitExpr;
    node->boolval = value;
    return node;
}

ASTNode *create_char_node(char value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeCharLitExpr;
    node->charval = value;
    return node;
}

ASTNode *create_string_node(char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeStringLitExpr;
    node->strval = strdup(value);
    return node;
}

ASTNode *create_identifier_node(char *name) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeIdentiferExpr;
    node->strval = strdup(name);
    return node;
}

ASTNode *create_binary_node(const char *op, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeBinaryExpr;
    node->binary_expr.op = op;
    node->binary_expr.left = left;
    node->binary_expr.right = right;
    return node;
}

ASTNode *create_unary_node(const char *op, ASTNode *operand) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeUnaryExpr;
    node->unary_expr.op = op;
    node->unary_expr.operand = operand;
    return node;
}

ASTNode *create_function_call_node(char *func_name, ASTNode **args, int arg_count) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeFunctionCallStmt;
    node->function_call_stmt.func_name = strdup(func_name);
    node->function_call_stmt.args = args;
    node->function_call_stmt.arg_count = arg_count;
    return node;
}

ASTNode *create_statement_list_node(ASTNode **statements, size_t count) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeBlockStmt;
    node->statement_list.statements = statements;
    node->statement_list.count = count;
    return node;
}

ASTNode* create_for_node(ASTNode* init, ASTNode* condition, ASTNode* increment, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NodeForStmt;
    node->for_loop_stmt.init = init;
    node->for_loop_stmt.condition = condition;
    node->for_loop_stmt.increment = increment;
    node->for_loop_stmt.body = body;
    return node;
}

ASTNode *create_var_decl_node(char *name, char *type, ASTNode *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeVarDeclStmt;
    node->var_decl_stmt.name = strdup(name);
    node->var_decl_stmt.type = strdup(type);
    node->var_decl_stmt.value = value;
    node->typeStr = strdup(type);
    return node;
}

ASTNode* create_if_statement_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NodeIfStmt;
    node->if_stmt.condition = condition;
    node->if_stmt.then_branch = then_branch;
    node->if_stmt.else_branch = else_branch;
    return node;
}

ASTNode* create_variable_node(const char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = NodeVarExpr;
    node->variable.name = strdup(name);
    return node;
}

ASTNode *create_assignment_node(char *var_name, ASTNode *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeAssignmentExpr;
    node->assignment_expr.var_name = strdup(var_name);
    node->assignment_expr.value = value;
    return node;
}

ASTNode *create_function_decl_node(char *name, char *return_type, char **param_names, char **param_types, int param_count, ASTNode *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeFunctionDefStmt;
    node->function_def_stmt.name = strdup(name);
    node->function_def_stmt.return_type = strdup(return_type);
    node->function_def_stmt.param_names = param_names;
    node->function_def_stmt.param_types = param_types;
    node->function_def_stmt.param_count = param_count;
    node->function_def_stmt.body = body;
    return node;
}

ASTNode *create_param_node(char *name, char *type) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_PARAM;
    node->param.name = strdup(name);
    node->param.type = strdup(type);
    return node;
}

ASTNode *create_param_list(void) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_PARAM_LIST;
    node->param_list.params = NULL;
    node->param_list.count = 0;
    return node;
}

ASTNode *create_while_node(ASTNode *condition, ASTNode *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeWhileStmt;
    node->while_stmt.condition = condition;
    node->while_stmt.body = body;
    return node;
}

ASTNode *create_println_node(ASTNode *expr) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodePrintLnExpr;
    node->println_expr.expr = expr;
    return node;
}

ASTNode *create_return_node(ASTNode *expr) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeReturnStmt;
    node->return_stmt.expr = expr;
    return node;
}

ASTNode *create_length_node(ASTNode *expr) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeLengthExpr;
    node->length_expr.expr = expr;
    return node;
}

ASTNode *create_typeof_node(ASTNode *expr) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeTypeOfExpr;
    node->typeof_expr.expr = expr;
    return node;
}

ASTNode *create_alloc_node(ASTNode *size) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeAllocExpr;
    node->alloc_expr.size = size;
    return node;
}

ASTNode *create_dealloc_node(ASTNode *pointer) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeDeallocExpr;
    node->dealloc_expr.pointer = pointer;
    return node;
}

ASTNode *create_sizeof_node(char *type) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeSizeOfExpr;
    node->sizeof_expr.type = strdup(type);
    return node;
}

ASTNode *create_unsafe_node(ASTNode *body) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeUnsafeExpr;
    node->unsafe_expr.body = body;
    return node;
}

ASTNode *create_arg_list(void) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_ARG_LIST;
    node->arg_list.args = NULL;
    node->arg_list.count = 0;
    return node;
}

ASTNode *create_cast_node(ASTNode *expr, char *type) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NodeCastExpr;
    node->cast_expr.expr = expr;
    node->cast_expr.type = type;
    return node;
}

void add_arg_to_list(ASTNode *list, ASTNode *arg) {
    list->arg_list.count++;
    list->arg_list.args = realloc(list->arg_list.args, (size_t)list->arg_list.count * sizeof(ASTNode*));
    list->arg_list.args[list->arg_list.count - 1] = arg;
}

void add_param_to_list(ASTNode *list, ASTNode *param) {
    if (list->type != NODE_PARAM_LIST) {
        fprintf(stderr, "Error: Trying to add parameter to a non-param list node.\n");
        return;
    }
    list->param_list.params = realloc(list->param_list.params, sizeof(ASTNode *) * (size_t)(list->param_list.count + 1));
    list->param_list.params[list->param_list.count++] = param;
}

void print_indent(int indent) {
    for (int i = 0; i < indent; ++i)
        printf("    ");
}

void free_ast(ASTNode *node) {
    if (node == NULL) return;

    switch (node->type) {  
        case NodeIntLitExpr:
        case NodeFloatLitExpr:
        case NodeBoolLitExpr:
        case NodeCharLitExpr:
            break;
        case NodeStringLitExpr:
            free(node->strval);
            break;
        case NodeIdentiferExpr:
            free(node->strval);
            break;
        case NodeBinaryExpr:
            free_ast(node->binary_expr.left);
            free_ast(node->binary_expr.right);
            break;
        case NodeUnaryExpr:
            free_ast(node->unary_expr.operand);
            break;
        case NodeFunctionCallStmt:
            free(node->function_call_stmt.func_name);
            for (int i = 0; i < node->function_call_stmt.arg_count; ++i) {
                free_ast(node->function_call_stmt.args[i]);
            }
            free(node->function_call_stmt.args);
            break;
        case NodeBlockStmt:
            for (size_t i = 0; i < node->statement_list.count; ++i) {
                free_ast(node->statement_list.statements[i]);
            }
            free(node->statement_list.statements);
            break;
        case NodeVarDeclStmt:
            free(node->var_decl_stmt.name);
            free(node->var_decl_stmt.type);  // Add this line to free the strdup'd type string
            free_ast(node->var_decl_stmt.value);
            break;
        case NodeAssignmentExpr:
            free(node->assignment_expr.var_name);
            free_ast(node->assignment_expr.value);
            break;
        case NodeIfStmt:
            free_ast(node->if_stmt.condition);
            free_ast(node->if_stmt.then_branch);
            free_ast(node->if_stmt.else_branch);
            break;
        case NodeVarExpr:
            free(node->variable.name);
            break;
        case NodeFunctionDefStmt:
            free(node->function_def_stmt.name);
            free(node->function_def_stmt.return_type);
            for (int i = 0; i < node->function_def_stmt.param_count; ++i) {
                free(node->function_def_stmt.param_names[i]);
                free(node->function_def_stmt.param_types[i]);
            }
            free(node->function_def_stmt.param_names);
            free(node->function_def_stmt.param_types);
            free_ast(node->function_def_stmt.body);
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
        case NodeWhileStmt:
            free_ast(node->while_stmt.condition);
            free_ast(node->while_stmt.body);
            break;
        case NodePrintLnExpr:
            free_ast(node->println_expr.expr);
            break;
        case NodeReturnStmt:
            free_ast(node->return_stmt.expr);
            break;
        case NodeLengthExpr:
            free_ast(node->length_expr.expr);
            break;
        case NodeTypeOfExpr:
            free_ast(node->typeof_expr.expr);
            break;
        case NodeAllocExpr:
            free_ast(node->alloc_expr.size);
            break;
        case NodeSizeOfExpr:
            free(node->sizeof_expr.type);
            break;
        case NodeUnsafeExpr:
            free_ast(node->unsafe_expr.body);
            break;
        case NodeDeallocExpr:
            free_ast(node->dealloc_expr.pointer);
            break;
        case NodeForStmt:
            free_ast(node->for_loop_stmt.init);
            free_ast(node->for_loop_stmt.body);
            free_ast(node->for_loop_stmt.condition);
            free_ast(node->for_loop_stmt.increment);
            break;
        case NodeCastExpr:
            free_ast(node->cast_expr.expr);
            free(node->cast_expr.type);
            break;
        default:
            printf("Unknown node type, skipping free operation.\n");
            break;
    }

    free(node);
}

void print_ast(ASTNode *node, int indent) {
    if (!node) return;

    print_indent(indent);
    switch (node->type) {
        case NodeIntLitExpr:
            printf("IntLiteral: %d\n", node->intval);
            break;
        case NodeFloatLitExpr:
            printf("FloatLiteral: %f\n", node->floatval);
            break;
        case NodeBoolLitExpr:
            printf("BoolLiteral: %s\n", node->boolval ? "true" : "false");
            break;
        case NodeCharLitExpr:
            printf("CharLiteral: '%c'\n", node->charval);
            break;
        case NodeStringLitExpr:
            printf("StringLiteral: %s\n", node->strval);
            break;
        case NodeIdentiferExpr:
            printf("Identifier: %s\n", node->strval);
            break;
        case NodeBinaryExpr:
            printf("BinaryExpr: '%s' (", node->binary_expr.op);
            print_ast_inline(node->binary_expr.left);
            printf(", ");
            print_ast_inline(node->binary_expr.right);
            printf(")\n");
            break;
        case NodeUnaryExpr:
            printf("UnaryExpr: '%s' (", node->unary_expr.op);
            print_ast_inline(node->unary_expr.operand);
            printf(")\n");
            break;
        case NodeFunctionCallStmt:
            printf("FunctionCall: %s(", node->function_call_stmt.func_name);
            for (int i = 0; i < node->function_call_stmt.arg_count; ++i) {
                if (i > 0) printf(", ");
                print_ast_inline(node->function_call_stmt.args[i]);
            }
            printf(")\n");
            break;
        case NodeBlockStmt:
            printf("BlockStmt:\n");
            for (size_t i = 0; i < node->statement_list.count; ++i) {
                print_ast(node->statement_list.statements[i], indent + 1);
            }
            break;
        case NodeVarExpr:
            printf("Variable: %s\n", node->variable.name);
            break;
        case NodeVarDeclStmt:
            printf("VarDecl: %s %s", node->var_decl_stmt.type, node->var_decl_stmt.name);
            if (node->var_decl_stmt.value) {
                printf(" = ");
                print_ast_inline(node->var_decl_stmt.value);
            }
            printf("\n");
            break;
        case NodeIfStmt:
            printf("If (");
            print_ast_inline(node->if_stmt.condition);
            printf(")\n");
            print_indent(indent + 1);
            printf("Then:\n");
            print_ast(node->if_stmt.then_branch, indent + 2);
            if (node->if_stmt.else_branch) {
                print_indent(indent + 1);
                printf("Else:\n");
                print_ast(node->if_stmt.else_branch, indent + 2);
            }
            break;
        case NodeAssignmentExpr:
            printf("Assignment: %s = ", node->assignment_expr.var_name);
            print_ast_inline(node->assignment_expr.value);
            printf("\n");
            break;
        case NodeFunctionDefStmt:
            printf("FunctionDef: %s() -> %s\n", node->function_def_stmt.name, node->function_def_stmt.return_type);
            print_ast(node->function_def_stmt.body, indent + 1);
            break;
        case NodeWhileStmt:
            printf("While (");
            print_ast_inline(node->while_stmt.condition);
            printf(")\n");
            print_ast(node->while_stmt.body, indent + 1);
            break;
        case NodePrintLnExpr:
            printf("PrintLn: ");
            print_ast_inline(node->println_expr.expr);
            printf("\n");
            break;
        case NodeReturnStmt:
            printf("Return: ");
            print_ast_inline(node->return_stmt.expr);
            printf("\n");
            break;
        case NodeLengthExpr:
            printf("Length: ");
            print_ast_inline(node->length_expr.expr);
            printf("\n");
            break;
        case NodeTypeOfExpr:
            printf("TypeOf: ");
            print_ast_inline(node->typeof_expr.expr);
            printf("\n");
            break;
        case NodeAllocExpr:
            printf("Alloc(size = ");
            print_ast_inline(node->alloc_expr.size);
            printf(")\n");
            break;
        case NodeDeallocExpr:
            printf("Dealloc: ");
            print_ast_inline(node->dealloc_expr.pointer);
            printf("\n");
            break;
        case NodeSizeOfExpr:
            printf("Sizeof: %s\n", node->sizeof_expr.type);
            break;
        case NodeUnsafeExpr:
            printf("UnsafeBlock:\n");
            print_ast(node->unsafe_expr.body, indent + 1);
            break;
        case NodeForStmt:
            printf("For (");
            print_ast_inline(node->for_loop_stmt.init);
            printf("; ");
            print_ast_inline(node->for_loop_stmt.condition);
            printf("; ");
            print_ast_inline(node->for_loop_stmt.increment);
            printf(")\n");
            print_ast(node->for_loop_stmt.body, indent + 1);
            break;
        case NodeCastExpr:
            printf("Cast:\n");
            print_indent(indent + 1);
            printf("Expression: ");
            print_ast_inline(node->cast_expr.expr);
            printf("\n");
            print_indent(indent + 1);
            printf("Type: %s\n", node->cast_expr.type);
            break;
        default:
            printf("Unknown node type!\n");
    }
}

void print_ast_inline(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NodeIntLitExpr:
            printf("IntLiteral: %d", node->intval);
            break;
        case NodeVarExpr:
            printf("Variable: %s", node->variable.name);
            break;
        case NodeSizeOfExpr:
            printf("Sizeof: %s", node->sizeof_expr.type);
            break;
        case NodeBinaryExpr:
            printf("BinaryExpr: '%s' (", node->binary_expr.op);
            print_ast_inline(node->binary_expr.left);
            printf(", ");
            print_ast_inline(node->binary_expr.right);
            printf(")");
            break;
        case NodeAllocExpr:
            printf("Alloc(size = ");
            print_ast_inline(node->alloc_expr.size);
            printf(")");
            break;
        case NodeUnaryExpr:
            printf("UnaryExpr: '%s' (", node->unary_expr.op);
            print_ast_inline(node->unary_expr.operand);
            printf(")");
            break;
        case NodeDeallocExpr:
            printf("Dealloc: ");
            print_ast_inline(node->dealloc_expr.pointer);
            break;
        case NodeAssignmentExpr:
            printf("Assignment: %s = ", node->assignment_expr.var_name);
            print_ast_inline(node->assignment_expr.value);
            break;
        case NodeLengthExpr:
            printf("Length: ");
            print_ast_inline(node->length_expr.expr);
            break;
        case NodeTypeOfExpr:
            printf("TypeOf: ");
            print_ast_inline(node->typeof_expr.expr);
            break;
        default:
            print_ast(node, 0);
    }
}
