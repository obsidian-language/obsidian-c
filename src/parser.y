%{
#if defined (__linux__) || defined (__unix__) || defined (__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.h"

extern FILE *yyin;
extern ASTNode *root;

ASTNode *root = NULL;
int yylex(void);
void yyerror(const char *s);

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
%}

%union {
    int intval;
    double floatval;
    char* strval;
    char charval;
    int boolval;
    struct ASTNode* node;
}

%token <intval> IntLit
%token <floatval> FloatLit
%token <charval> CharLit
%token <strval> StringLit
%token <boolval> BoolLit
%token <strval> Ident

%left Plus Minus
%left Star Slash Percent
%right Power
%left LogicalAnd LogicalOr

%token LParen RParen LBrace RBrace LBracket RBracket Plus Minus Star Slash Dot Colon Semi Comma Not Greater Less Carot Percent Assign Ampersand Pipe Question XorNot
%token Power LogicalAnd LogicalOr PlusAssign MinusAssign StarAssign SlashAssign Equal NotEqual GreaterEqual LessEqual
%token Decrement Increment Xor RightShift LeftShift
%token I8 I16 I32 I64 U8 U16 U32 U64 F32 F64 String Char Bool Void Const Fn If Else Switch Case Default While For Return Struct Enum New Null Alloc Dealloc Unsafe Sizeof Private Typeof Import Export Cast PrintLn Length Break

%type <node> program statements statement expr if_stmt func_def param_list param while_stmt arg_list unsafe_stmt for_stmt primary
%type <strval> type

%%

program:
    statements { root = $1; }
    ;

statements:
      statement { 
            ASTNode **stmts = malloc(sizeof(ASTNode*)); 
            stmts[0] = $1;
            $$ = create_statement_list_node(stmts, 1); 
      }
    | statements statement { 
            size_t count = $1->statement_list.count + 1; 
            $1->statement_list.statements = realloc($1->statement_list.statements, count * sizeof(ASTNode*)); 
            $1->statement_list.statements[count - 1] = $2; 
            $1->statement_list.count = count; 
            $$ = $1; 
      }
    ;

statement:
      expr Semi                  { $$ = $1; }
    | if_stmt                    { $$ = $1; }
    | func_def                   { $$ = $1; }
    | while_stmt                 { $$ = $1; }
    | for_stmt                   { $$ = $1; }
    | unsafe_stmt                { $$ = $1; }
    ;

type:
      I8      { $$ = strdup("i8"); }
    | I16     { $$ = strdup("i16"); }
    | I32     { $$ = strdup("i32"); }
    | I64     { $$ = strdup("i64"); }
    | U8      { $$ = strdup("u8"); }
    | U16     { $$ = strdup("u16"); }
    | U32     { $$ = strdup("u32"); }
    | U64     { $$ = strdup("u64"); }
    | F32     { $$ = strdup("f32"); }
    | F64     { $$ = strdup("f64"); }
    | Bool    { $$ = strdup("bool"); }
    | Char    { $$ = strdup("char"); }
    | String  { $$ = strdup("string"); }
    | Void    { $$ = strdup("void"); }
    ;

primary:
      IntLit         { $$ = create_int_node($1); }
    | FloatLit       { $$ = create_float_node($1); }
    | StringLit      { $$ = create_string_node($1); }
    | CharLit        { $$ = create_char_node($1); }
    | BoolLit        { $$ = create_bool_node($1); }
    | Ident          { $$ = create_variable_node($1); }
    | LParen expr RParen  { $$ = $2; }
    ;

expr:
      primary
    | expr Plus primary             { $$ = create_binary_node("+", $1, $3); }
    | expr Minus primary            { $$ = create_binary_node("-", $1, $3); }
    | expr Star primary             { $$ = create_binary_node("*", $1, $3); }
    | expr Slash primary            { $$ = create_binary_node("/", $1, $3); }
    | expr Percent primary          { $$ = create_binary_node("%", $1, $3); }
    | expr Power primary            { $$ = create_binary_node("**", $1, $3); }
    | expr Greater primary          { $$ = create_binary_node(">", $1, $3); }
    | expr Less primary             { $$ = create_binary_node("<", $1, $3); }
    | expr LogicalOr primary        { $$ = create_binary_node("||", $1, $3); }
    | expr LogicalAnd primary       { $$ = create_binary_node("&&", $1, $3); }
    | expr Equal primary            { $$ = create_binary_node("==", $1, $3); }
    | expr NotEqual primary         { $$ = create_binary_node("!=", $1, $3); }
    | expr GreaterEqual primary     { $$ = create_binary_node(">=", $1, $3); }
    | expr LessEqual primary        { $$ = create_binary_node("<=", $1, $3); }
    | expr Carot primary            { $$ = create_binary_node("^", $1, $3); }
    | expr Ampersand primary        { $$ = create_binary_node("&", $1, $3); }
    | expr Pipe primary             { $$ = create_binary_node("|", $1, $3); }
    | expr Xor primary              { $$ = create_binary_node("^^", $1, $3); }
    | expr RightShift primary       { $$ = create_binary_node(">>", $1, $3); }
    | expr LeftShift primary        { $$ = create_binary_node("<<", $1, $3); }
    | expr PlusAssign primary       { $$ = create_binary_node("+=", $1, $3); }
    | expr MinusAssign primary      { $$ = create_binary_node("-=", $1, $3); }
    | expr StarAssign primary       { $$ = create_binary_node("*=", $1, $3); }
    | expr SlashAssign primary      { $$ = create_binary_node("/=", $1, $3); }
    | expr Increment                { $$ = create_unary_node("++", $1); }
    | expr Decrement                { $$ = create_unary_node("--", $1); }
    | XorNot primary                { $$ = create_unary_node("~", $2); }
    | Minus primary                 { $$ = create_unary_node("-", $2); }
    | Not primary                   { $$ = create_unary_node("!", $2); }
    | PrintLn LParen expr RParen    { $$ = create_println_node($3); } 
    | Return expr                   { $$ = create_return_node($2); }
    | Length LParen expr RParen     { $$ = create_length_node($3); }
    | Typeof LParen expr RParen     { $$ = create_typeof_node($3); }
    | Alloc LParen expr RParen      { $$ = create_alloc_node($3); }
    | Sizeof LParen type RParen     { $$ = create_sizeof_node($3); }
    | Dealloc LParen expr RParen    { $$ = create_dealloc_node($3); }
    | Ident LParen arg_list RParen  {
                                      ASTNode *argListNode = $3;
                                      int argCount = argListNode->arg_list.count;
                                      ASTNode **args = malloc(sizeof(ASTNode*) * (size_t)argCount);
                                      for (int i = 0; i < argCount; ++i) {
                                          args[i] = argListNode->arg_list.args[i];
                                      }
                                      $$ = create_function_call_node($1, args, argCount);
                                  }
    | Ident Assign expr             { $$ = create_assignment_node($1, $3); }
    | type Ident Assign expr        { $$ = create_var_decl_node($2, $1, $4); }
    | type Ident                    { $$ = create_var_decl_node($2, $1, NULL); }
    | Cast LParen expr Comma type RParen { $$ = create_cast_node($3, $5); }
    ;

if_stmt:
      If LParen expr RParen LBrace statements RBrace { $$ = create_if_statement_node($3, $6, NULL); }
    | If LParen expr RParen LBrace statements RBrace Else LBrace statements RBrace { $$ = create_if_statement_node($3, $6, $10); }
    ;

param:
      type Ident { $$ = create_param_node($2, $1); }
    ;

unsafe_stmt:
      Unsafe LBrace statements RBrace { $$ = create_unsafe_node($3); }
    ;

arg_list:
      /* empty */       { $$ = create_arg_list(); }
    | expr              { $$ = create_arg_list(); add_arg_to_list($$, $1); }
    | arg_list Comma expr { add_arg_to_list($1, $3); $$ = $1; }
    ;

param_list:
      /* empty */       { $$ = create_param_list(); }
    | param             { $$ = create_param_list(); add_param_to_list($$, $1); }
    | param_list Comma param { add_param_to_list($1, $3); $$ = $1; }
    ;

func_def:
      Fn Ident LParen param_list RParen type LBrace statements RBrace {
            ASTNode *paramListNode = $4;
            int paramCount = paramListNode->param_list.count;
            char **paramNames = malloc(sizeof(char*) * (size_t)paramCount);
            char **paramTypes = malloc(sizeof(char*) * (size_t)paramCount);
            for (int i = 0; i < paramCount; ++i) {
                paramNames[i] = strdup(paramListNode->param_list.params[i]->param.name);
                paramTypes[i] = strdup(paramListNode->param_list.params[i]->param.type);
            }
            $$ = create_function_decl_node($2, $6, paramNames, paramTypes, paramCount, $8);
      }
    ;

while_stmt:
      While LParen expr RParen LBrace statements RBrace { $$ = create_while_node($3, $6); }
    ;

for_stmt:
      For LParen expr Semi expr Semi expr RParen LBrace statements RBrace { $$ = create_for_node($3, $5, $7, $10); }
    ;

%%
