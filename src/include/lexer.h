#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TLparen, TRparen, TLbrace, TRbrace, TLbracket, TRbracket, TPlus, TMinus, TStar, TSlash, TDot, TColon, TSemi, TComma, TNot, TGreater, TLess, TCarot, TPercent, TAssign, TAmpersand, TPipe,
    TQuestion, TPower, TLogicalOr, TLogicalAnd, TPlusAssign, TMinusAssign, TStarAssign, TSlashAssign, TEqual, TNotEqual, TGreaterEqual, TLessEqual, TDecrement, TIncrement, TXor, TLeftShift, TRightShift,
    TI8, TI16, TI32, TI64, TF32, TF64, TU8, TU16, TU32, TU64, TString, TChar, TBool, TVoid, TConst, TFn, TIf, TElse, TSwitch, TCase, TDefault, TWhile, TFor, TReturn, TStruct, TEnum, TNew, TNull, TTrue, TFalse, TAlloc, TDealloc, TUnsafe,
    TSizeof, TPrivate, TTypeof, TImport, TExport, TCast, TPrintln, TLength, TBreak, TEof, TError, TIntLiteral, TFloatLiteral, TBoolLiteral, TStringLiteral, TCharLiteral, TIdentifier
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