%{
#if defined (__linux__) || defined (__unix__) || defined (__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/ast.h"

extern FILE *yyin;
extern ASTNode *root;

ASTNode *root = NULL;
int yylex(void);
void yyerror(const char *s);

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
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

%token LParen RParen LBrace RBrace LBracket RBracket Plus Minus Star Slash Dot Colon Semi Comma Not Greater Less Carot Percent Assign Ampersand Pipe Question XorNot Power LogicalAnd LogicalOr PlusAssign MinusAssign StarAssign SlashAssign Equal NotEqual GreaterEqual LessEqual Decrement Increment Xor RightShift LeftShift I8 I16 I32 I64 U8 U16 U32 U64 F32 F64 String Char Bool Void Const Fn If Else Switch Case Default While For Return Struct Enum New Null Alloc Dealloc Unsafe Sizeof Private Typeof Import Export Cast PrintLn Length Break

%type <node> expr declaration
%type <strval> type

%%

program:
    declaration Semi { root = $1; };

type:
    I8  { $$ = strdup("i8"); }
  | I16 { $$ = strdup("i16"); }
  | I32 { $$ = strdup("i32"); }
  | I64 { $$ = strdup("i64"); }
  | U8  { $$ = strdup("u8"); }
  | U16 { $$ = strdup("u16"); }
  | U32 { $$ = strdup("u32"); }
  | U64 { $$ = strdup("u64"); }
  | F32 { $$ = strdup("f32"); }
  | F64 { $$ = strdup("f64"); }
  | Bool { $$ = strdup("bool"); }
  | Char { $$ = strdup("char"); }
  | String { $$ = strdup("string"); }
  | Void { $$ = strdup("void"); };

declaration:
    type Ident Assign expr { $$ = create_var_decl_node($2, $1, $4); };

expr:
    expr Plus expr { $$ = create_binary_node("+", $1, $3); }
    | expr Minus expr { $$ = create_binary_node("-", $1, $3); }
    | expr Star expr { $$ = create_binary_node("*", $1, $3); }
    | expr Slash expr { $$ = create_binary_node("/", $1, $3); }
    | expr Percent expr { $$ = create_binary_node("%", $1, $3); }
    | expr Power expr { $$ = create_binary_node("**", $1, $3); }
    | expr Greater expr { $$ = create_binary_node(">", $1, $3); }
    | expr Less expr { $$ = create_binary_node("<", $1, $3); }
    | expr LogicalOr expr { $$ = create_binary_node("||", $1, $3); }
    | expr LogicalAnd expr { $$ = create_binary_node("&&", $1, $3); }
    | expr Equal expr { $$ = create_binary_node("==", $1, $3); }
    | expr NotEqual expr { $$ = create_binary_node("!=", $1, $3); }
    | expr GreaterEqual expr { $$ = create_binary_node(">=", $1, $3); }
    | expr LessEqual expr { $$ = create_binary_node("<=", $1, $3); }
    | expr Carot expr { $$ = create_binary_node("^", $1, $3); }
    | expr Ampersand expr { $$ = create_binary_node("&", $1, $3); }
    | expr Pipe expr { $$ = create_binary_node("|", $1, $3); }
    | expr Xor expr { $$ = create_binary_node("^^", $1, $3); }
    | expr RightShift expr { $$ = create_binary_node(">>", $1, $3); }
    | expr LeftShift expr { $$ = create_binary_node("<<", $1, $3); }
    | expr PlusAssign expr { $$ = create_binary_node("+=", $1, $3); }
    | expr MinusAssign expr { $$ = create_binary_node("-=", $1, $3); }
    | expr StarAssign expr { $$ = create_binary_node("*=", $1, $3); }
    | expr SlashAssign expr { $$ = create_binary_node("/=", $1, $3); }
    | expr Increment { $$ = create_unary_node("++", $1); }
    | expr Decrement { $$ = create_unary_node("--", $1); }
    | XorNot expr { $$ = create_unary_node("~", $2); }
    | Minus expr { $$ = create_unary_node("-", $2); }
    | Not expr { $$ = create_unary_node("!", $2); }
    | LParen expr RParen { $$ = $2; }
    | IntLit { $$ = create_int_node($1); }
    | FloatLit { $$ = create_float_node($1); };
    | StringLit { $$ = create_string_node($1); }
    | CharLit { $$ = create_char_node($1); }
    | BoolLit { $$ = create_bool_node($1); }

%%
