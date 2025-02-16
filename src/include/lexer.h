#ifndef LEXER_H
#define LEXER_H

typedef enum {
    Lparen, Rparen, Lbrace, Rbrace, Lbracket, Rbracket, Plus, Minus, Star, Slash, Dot, Colon, Semi, Comma, Not, Greater, Less, Carot, Percent, Assign, Ampersand, Pipe,
    Power, LogicalOr, LogicalAnd, PlusAssign, MinusAssign, StarAssign, SlashAssign, Equal, NotEqual, GreaterEqual, LessEqual, Decrement, Increment, Xor, LeftShift, RightShift,
    I8, I16, I32, I64, F32, F64, U8, U16, U32, U64, String, Char, Bool, Void, Const, Fn, If, Else, Switch, Case, Default, While, For, Return, Struct, Enum, New, Null, True, False, Alloc, Dealloc, Unsafe,
    Sizeof, Private, Typeof, Import, Export, Cast, Println, Length, Break, Eof, Error, IntLiteral, FloatLiteral, BoolLiteral, StringLiteral, CharLiteral, Identifier
} TokenKind;

typedef struct {
    TokenKind type;
    char *start;
    int length;
    int line, column;
} Token;

typedef struct {
    char *start;
    char *current;
    int line, column;
} Lexer;

typedef struct {
    const char *keyword;
    TokenKind token;
} KeywordEntry;

void initLexer(Lexer *lexer, char *source);

Token getNextToken(Lexer *lexer);

int isEndOfFile(Lexer *lexer);

void skipWhitespace(Lexer *lexer);

#endif // LEXER_H