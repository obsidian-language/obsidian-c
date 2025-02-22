#include "include/lexer.h"
#include "include/error.h"
#include <ctype.h>
#include <string.h>

#define KEYWORD_COUNT (sizeof(keywords) / sizeof(keywords[0]))

static const KeywordEntry keywords[] = {
    {"if", TIf}, {"else", TElse}, {"while", TWhile}, {"for", TFor}, {"return", TReturn}, {"const", TConst},
    {"fn", TFn}, {"switch", TSwitch}, {"case", TCase}, {"default", TDefault}, {"struct", TStruct},
    {"enum", TEnum}, {"new", TNew}, {"null", TNull}, {"true", TTrue}, {"false", TFalse},
    {"alloc", TAlloc}, {"dealloc", TDealloc}, {"unsafe", TUnsafe}, {"sizeof", TSizeof},
    {"private", TPrivate}, {"typeof", TTypeof}, {"import", TImport}, {"export", TExport},
    {"cast", TCast}, {"println", TPrintln}, {"length", TLength}, {"break", TBreak},
    {"i8", TI8}, {"i16", TI16}, {"i32", TI32}, {"i64", TI64}, {"f32", TF32}, {"f64", TF64},
    {"u8", TU8}, {"u16", TU16}, {"u32", TU32}, {"u64", TU64}, {"string", TString}, {"bool", TBool}, {"void", TVoid}, {"char", TChar}
};

void initLexer(Lexer *lexer, char *source) {
    lexer->start = source;
    lexer->current = source;
    lexer->line = 1;
    lexer->column = 1;
}

TokenKind checkKeyword(const char *start, int length) {
    for (size_t i = 0; i < KEYWORD_COUNT; i++) {
        if (strncmp(start, keywords[i].keyword, length) == 0 && keywords[i].keyword[length] == '\0') {
            return keywords[i].token;
        }
    }
    return TIdentifier;
}

Token getNextToken(Lexer *lexer) {
    skipWhitespace(lexer);

    Token token = {0};
    token.start = lexer->current;
    token.line = lexer->line;
    token.column = lexer->column;

    char c = *lexer->current;
    lexer->current++;
    lexer->column++;

    #define matchNext(expected, typeIfMatch, typeElse) \
        ( *lexer->current == (expected) ? (lexer->current++, lexer->column++, (typeIfMatch)) : (typeElse) )

    switch (c) {
        case '(': token.type = TLparen;   break;
        case ')': token.type = TRparen;   break;
        case '{': token.type = TLbrace;   break;
        case '}': token.type = TRbrace;   break;
        case '[': token.type = TLbracket; break;
        case ']': token.type = TRbracket; break;
        case '.': token.type = TDot;      break;
        case ':': token.type = TColon;    break;
        case ';': token.type = TSemi;     break;
        case ',': token.type = TComma;    break;
        case '?': token.type = TQuestion; break;
        case '%': token.type = TPercent;  break;
        case '^': token.type = matchNext('^', TXor, TCarot); break;
        case '+': token.type = matchNext('+', TIncrement, matchNext('=', TPlusAssign, TPlus)); break;
        case '-': token.type = matchNext('-', TDecrement, matchNext('=', TMinusAssign, TMinus)); break;
        case '*': token.type = matchNext('=', TStarAssign, matchNext('*', TPower, TStar)); break;
        case '/': token.type = matchNext('=', TSlashAssign, TSlash); break;
        case '!': token.type = matchNext('=', TNotEqual, TNot); break;
        case '=': token.type = matchNext('=', TEqual, TAssign); break;
        case '&': token.type = matchNext('&', TLogicalAnd, TAmpersand); break;
        case '|': token.type = matchNext('|', TLogicalOr, TPipe); break;
        case '>': 
            token.type = matchNext('=', TGreaterEqual, matchNext('>', TRightShift, TGreater));
            break;
        case '<': 
            token.type = matchNext('=', TLessEqual, matchNext('<', TLeftShift, TLess));
            break;

        case '"': {
            const char *start = lexer->current;
            while (*lexer->current != '"' && *lexer->current != '\0') {
                lexer->current++;
                lexer->column++;
            }
            if (*lexer->current == '"') {
                lexer->current++;
                lexer->column++;
                token.type = TStringLiteral;
                token.length = lexer->current - start + 1;
            } else {
                error("Unterminated string literal", &token);
                token.type = TError;
            }
            return token;
        }

        case '\'': {
            const char *start = lexer->current;
            if (*lexer->current == '\\') {
                lexer->current++;
                lexer->column++;
            }
            lexer->current++;
            lexer->column++;
            if (*lexer->current == '\'') {
                lexer->current++;
                lexer->column++;
                token.type = TCharLiteral;
                token.length = lexer->current - start + 1;
            } else {
                error("Unterminated character literal", &token);
                token.type = TError;
            }
            return token;
        }

        case '\0': token.type = TEof; break;

        default:
            if (isalpha(c)) {
                const char *start = lexer->current - 1;
                while (isalnum(*lexer->current)) {
                    lexer->current++;
                    lexer->column++;
                }
                token.type = checkKeyword(start, lexer->current - start);
                token.length = lexer->current - start;
                return token;
            }

            if (isdigit(c)) {
                const char *start = lexer->current - 1;
                while (isdigit(*lexer->current)) {
                    lexer->current++;
                    lexer->column++;
                }
                if (*lexer->current == '.') {
                    lexer->current++;
                    lexer->column++;
                    while (isdigit(*lexer->current)) {
                        lexer->current++;
                        lexer->column++;
                    }
                    token.type = TFloatLiteral;
                } else {
                    token.type = TIntLiteral;
                }
                token.length = lexer->current - start;
                return token;
            }

            error("Unexpected character", &token);
            token.type = TError;
            break;
    }

    token.length = lexer->current - token.start;
    return token;
}

int isEndOfFile(Lexer *lexer) {
    return *lexer->current == '\0';
}

void skipWhitespace(Lexer *lexer) {
    while (isspace(*lexer->current) || *lexer->current == '#') {
        if (*lexer->current == '\n') {
            lexer->line++;
            lexer->column = 1;
        } else {
            lexer->column++;
        }
        lexer->current++;
    }
}