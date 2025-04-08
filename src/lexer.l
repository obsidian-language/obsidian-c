%{
#include "parser.tab.h"
%}

%option noinput nounput

Digit           [0-9]
Letter          [a-zA-Z_]
Identifier      {Letter}({Letter}|{Digit})*
IntLiteral      {Digit}+
FloatLiteral    {Digit}+"."{Digit}*
CharLiteral     \'(\\.|[^\\'])\'
StringLiteral   \"(\\.|[^\\"])*\"

%%

"("                 { return LParen; }
")"                 { return RParen; }
"{"                 { return LBrace; }
"}"                 { return RBrace; }
"["                 { return LBracket; }
"]"                 { return RBracket; }
"+"                 { return Plus; }                 
"-"                 { return Minus; }
"*"                 { return Star; }
"/"                 { return Slash; }
"."                 { return Dot; }
":"                 { return Colon; }
";"                 { return Semi; }
","                 { return Comma; }
"!"                 { return Not; }
">"                 { return Greater; }
"<"                 { return Less; }
"^"                 { return Carot; }
"%"                 { return Percent; }
"="                 { return Assign; }
"&"                 { return Ampersand; }
"|"                 { return Pipe; }
"?"                 { return Question; }
"~"                 { return XorNot; }

"**"                { return Power; }
"||"                { return LogicalOr; }
"&&"                { return LogicalAnd; }
"+="                { return PlusAssign; }
"-="                { return MinusAssign; }
"*="                { return StarAssign; }
"/="                { return SlashAssign; }
"=="                { return Equal; }
"!="                { return NotEqual; }
">="                { return GreaterEqual; }
"<="                { return LessEqual; }
"--"                { return Decrement; }
"++"                { return Increment; }
"^^"                { return Xor; }
">>"                { return RightShift; }
"<<"                { return LeftShift; }

"i8"                { return I8; }
"i16"               { return I16; }
"i32"               { return I32; }
"i64"               { return I64; }
"u8"                { return U8; }
"u16"               { return U16; }
"u32"               { return U32; }
"u64"               { return U64; }
"f32"               { return F32; }
"f64"               { return F64; }
"string"            { return String; }
"char"              { return Char; }
"bool"              { return Bool; }
"void"              { return Void; }

"const"             { return Const; }
"fn"                { return Fn; }
"if"                { return If; }
"else"              { return Else; }
"switch"            { return Switch; }
"case"              { return Case; }
"default"           { return Default; }
"while"             { return While; }
"for"               { return For; }
"return"            { return Return; }
"struct"            { return Struct; }
"enum"              { return Enum; }
"new"               { return New; }
"null"              { return Null; }
"alloc"             { return Alloc; }
"dealloc"           { return Dealloc; }
"unsafe"            { return Unsafe; }
"sizeof"            { return Sizeof; }
"private"           { return Private; }
"typeof"            { return Typeof; }
"import"            { return Import; }
"export"            { return Export; }
"cast"              { return Cast; }
"println"           { return PrintLn; }
"length"            { return Length; }
"break"             { return Break; }

"true"              { yylval.boolval = 1; return BoolLit; }
"false"             { yylval.boolval = 0; return BoolLit; }
{CharLiteral}       { yylval.charval = yytext[1]; return CharLit; }
{StringLiteral}     { yylval.strval = strdup(yytext); return StringLit; }
{IntLiteral}        { yylval.intval = atoi(yytext); return IntLit; }
{FloatLiteral}      { yylval.floatval = strtof(yytext, NULL); return FloatLit; }
{Identifier}        { yylval.strval = strdup(yytext); return Ident; }

[ \t\r\n]+          { /* skip whitespace */ }
.                   { printf("Unexpected character: %s\n", yytext); }

%%

int yywrap(void) { return 1; }
