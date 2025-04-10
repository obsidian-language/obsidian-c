%{
#include "parser.h"
#include "error.h"
#include "color.h"
int yycolumn = 1;
const char *filename;
%}

%option noinput nounput

Digit           [0-9]
Letter          [a-zA-Z_]
Identifier      {Letter}({Letter}|{Digit})*
IntLiteral      {Digit}+
FloatLiteral    ({Digit}+"."{Digit}*|{Digit}*"."{Digit}+)
CharLiteral     \'(\\.|[^\\'])\'
StringLiteral   \"(\\.|[^\\"])*\"

%%

"@".*               { /* Ignore single-line comments */ }
"("                 { yycolumn += yyleng; return LParen; }
")"                 { yycolumn += yyleng; return RParen; }
"{"                 { yycolumn += yyleng; return LBrace; }
"}"                 { yycolumn += yyleng; return RBrace; }
"["                 { yycolumn += yyleng; return LBracket; }
"]"                 { yycolumn += yyleng; return RBracket; }
"+"                 { yycolumn += yyleng; return Plus; }                 
"-"                 { yycolumn += yyleng; return Minus; }
"*"                 { yycolumn += yyleng; return Star; }
"/"                 { yycolumn += yyleng; return Slash; }
"."                 { yycolumn += yyleng; return Dot; }
":"                 { yycolumn += yyleng; return Colon; }
";"                 { yycolumn += yyleng; return Semi; }
","                 { yycolumn += yyleng; return Comma; }
"!"                 { yycolumn += yyleng; return Not; }
">"                 { yycolumn += yyleng; return Greater; }
"<"                 { yycolumn += yyleng; return Less; }
"^"                 { yycolumn += yyleng; return Carot; }
"%"                 { yycolumn += yyleng; return Percent; }
"="                 { yycolumn += yyleng; return Assign; }
"&"                 { yycolumn += yyleng; return Ampersand; }
"|"                 { yycolumn += yyleng; return Pipe; }
"?"                 { yycolumn += yyleng; return Question; }
"~"                 { yycolumn += yyleng; return XorNot; }

"**"                { yycolumn += yyleng; return Power; }
"||"                { yycolumn += yyleng; return LogicalOr; }
"&&"                { yycolumn += yyleng; return LogicalAnd; }
"+="                { yycolumn += yyleng; return PlusAssign; }
"-="                { yycolumn += yyleng; return MinusAssign; }
"*="                { yycolumn += yyleng; return StarAssign; }
"/="                { yycolumn += yyleng; return SlashAssign; }
"=="                { yycolumn += yyleng; return Equal; }
"!="                { yycolumn += yyleng; return NotEqual; }
">="                { yycolumn += yyleng; return GreaterEqual; }
"<="                { yycolumn += yyleng; return LessEqual; }
"--"                { yycolumn += yyleng; return Decrement; }
"++"                { yycolumn += yyleng; return Increment; }
"^^"                { yycolumn += yyleng; return Xor; }
">>"                { yycolumn += yyleng; return RightShift; }
"<<"                { yycolumn += yyleng; return LeftShift; }

"i8"                { yycolumn += yyleng; return I8; }
"i16"               { yycolumn += yyleng; return I16; }
"i32"               { yycolumn += yyleng; return I32; }
"i64"               { yycolumn += yyleng; return I64; }
"u8"                { yycolumn += yyleng; return U8; }
"u16"               { yycolumn += yyleng; return U16; }
"u32"               { yycolumn += yyleng; return U32; }
"u64"               { yycolumn += yyleng; return U64; }
"f32"               { yycolumn += yyleng; return F32; }
"f64"               { yycolumn += yyleng; return F64; }
"string"            { yycolumn += yyleng; return String; }
"char"              { yycolumn += yyleng; return Char; }
"bool"              { yycolumn += yyleng; return Bool; }
"void"              { yycolumn += yyleng; return Void; }

"const"             { yycolumn += yyleng; return Const; }
"fn"                { yycolumn += yyleng; return Fn; }
"if"                { yycolumn += yyleng; return If; }
"else"              { yycolumn += yyleng; return Else; }
"switch"            { yycolumn += yyleng; return Switch; }
"case"              { yycolumn += yyleng; return Case; }
"default"           { yycolumn += yyleng; return Default; }
"while"             { yycolumn += yyleng; return While; }
"for"               { yycolumn += yyleng; return For; }
"return"            { yycolumn += yyleng; return Return; }
"struct"            { yycolumn += yyleng; return Struct; }
"enum"              { yycolumn += yyleng; return Enum; }
"new"               { yycolumn += yyleng; return New; }
"null"              { yycolumn += yyleng; return Null; }
"alloc"             { yycolumn += yyleng; return Alloc; }
"dealloc"           { yycolumn += yyleng; return Dealloc; }
"unsafe"            { yycolumn += yyleng; return Unsafe; }
"sizeof"            { yycolumn += yyleng; return Sizeof; }
"private"           { yycolumn += yyleng; return Private; }
"typeof"            { yycolumn += yyleng; return Typeof; }
"import"            { yycolumn += yyleng; return Import; }
"export"            { yycolumn += yyleng; return Export; }
"cast"              { yycolumn += yyleng; return Cast; }
"println"           { yycolumn += yyleng; return PrintLn; }
"length"            { yycolumn += yyleng; return Length; }
"break"             { yycolumn += yyleng; return Break; }

"true"              { yycolumn += yyleng; yylval.boolval = 1; return BoolLit; }
"false"             { yycolumn += yyleng; yylval.boolval = 0; return BoolLit; }
{CharLiteral}       { yycolumn += yyleng; yylval.charval = yytext[1]; return CharLit; }
{StringLiteral}     { yycolumn += yyleng; yylval.strval = strdup(yytext); return StringLit; }
{IntLiteral}        { yycolumn += yyleng; yylval.intval = atoi(yytext); return IntLit; }
{FloatLiteral}      { yycolumn += yyleng; yylval.floatval = strtof(yytext, NULL); return FloatLit; }
{Identifier}        { yycolumn += yyleng; yylval.strval = strdup(yytext); return Ident; }

[ \t\r]+            { yycolumn += yyleng; }
\n                  { yycolumn = 1; yylineno++; }
.                   { report_error("Unexpected Character", yytext); }

%%

int yywrap(void) { return 1; }
