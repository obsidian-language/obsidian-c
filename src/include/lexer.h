#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
typedef enum {
    TLparen, TRparen, TLbrace, TRbrace, TLbracket, TRbracket, TPlus, TMinus, TStar, TSlash, TDot, TColon, TSemi, TComma, TNot, TGreater, TLess, TCarot, TPercent, TAssign, TAmpersand, TPipe, TQuestion, TXorNot, TPower, TLogicalOr, TLogicalAnd, TPlusAssign, TMinusAssign, TStarAssign, TSlashAssign, TEqual, TNotEqual, TGreaterEqual, TLessEqual, TDecrement, TIncrement, TXor, TLeftShift, TRightShift, TI8, TI16, TI32, TI64, TF32, TF64, TU8, TU16, TU32, TU64, TString, TChar, TBool, TVoid, TConst, TFn, TIf, TElse, TSwitch, TCase, TDefault, TWhile, TFor, TReturn, TStruct, TEnum, TNew, TNull, TTrue, TFalse, TAlloc, TDealloc, TUnsafe, TSizeof, TPrivate, TTypeof, TImport, TExport, TCast, TPrintln, TLength, TBreak, TEof, TError, TIntLiteral, TFloatLiteral, TBoolLiteral, TStringLiteral, TCharLiteral, TIdentifier, TReturnType, TUnknown
} TokenKind;

typedef struct {
    TokenKind type;
    char *start;
    int length, line, column;
} Token;

typedef struct {
    char *start, *current;
    int line, column;
} Lexer;

typedef struct {
    const char *keyword;
    TokenKind token;
} KeywordEntry;

void initLexer(Lexer *lexer, char *source);

Token getNextToken(Lexer *lexer);

void skipWhitespace(Lexer *lexer);

int compareKeywords(const void *a, const void *b);

TokenKind checkKeyword(const char *start, size_t length);

#endif // LEXER_H
