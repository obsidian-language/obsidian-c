#include "include/lexer.h"
#include "include/error.h"
#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

static KeywordEntry keywords[] = {
    {"alloc", TAlloc}, {"break", TBreak}, {"case", TCase}, {"char", TChar}, {"const", TConst}, {"dealloc", TDealloc}, {"default", TDefault}, {"else", TElse}, {"enum", TEnum}, {"export", TExport}, {"false", TFalse}, {"fn", TFn}, {"for", TFor}, {"if", TIf}, {"import", TImport}, {"i8", TI8}, {"i16", TI16}, {"i32", TI32}, {"i64", TI64}, {"length", TLength}, {"new", TNew}, {"null", TNull}, {"private", TPrivate}, {"println", TPrintln}, {"return", TReturn}, {"sizeof", TSizeof}, {"string", TString}, {"struct", TStruct}, {"switch", TSwitch}, {"true", TTrue}, {"typeOf", TTypeof}, {"unsafe", TUnsafe}, {"u8", TU8}, {"u16", TU16}, {"u32", TU32}, {"u64", TU64}, {"void", TVoid}, {"while", TWhile}
};

int compareKeywords(const void *a, const void *b) {
    return strcmp(((KeywordEntry *)a)->keyword, ((KeywordEntry *)b)->keyword);
}

void initLexer(Lexer *lexer, char *source) {
    lexer->start = source;
    lexer->current = source;
    lexer->line = 1;
    lexer->column = 1;
}

TokenKind checkKeyword(const char *start, size_t length) {
    char keyword[length + 1];
    memcpy(keyword, start, length);
    keyword[length] = '\0';

    KeywordEntry key = { .keyword = keyword };
    KeywordEntry *result = bsearch(&key, keywords, sizeof(keywords) / sizeof(keywords[0]), sizeof(KeywordEntry), compareKeywords);

    return (result && strcmp(result->keyword, keyword) == 0) ? result->token : TIdentifier;
}

Token getNextToken(Lexer *lexer) {
    Token token;
    char c;

    skipWhitespace(lexer);

    token.type = TUnknown;
    token.start = lexer->current;
    token.line = lexer->line;
    token.column = lexer->column;

    c = *lexer->current;
    lexer->current++;
    lexer->column++;

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
        case '^': token.type = (*lexer->current == '^') ? (lexer->current++, lexer->column++, TXor) : TCarot; break;
        case '+': token.type = (*lexer->current == '+') ? (lexer->current++, lexer->column++, TIncrement) : ((*lexer->current == '=') ? (lexer->current++, lexer->column++, TPlusAssign) : TPlus); break;
        case '-': token.type = (*lexer->current == '-') ? (lexer->current++, lexer->column++, TDecrement) : ((*lexer->current == '=') ? (lexer->current++, lexer->column++, TMinusAssign) : TMinus); break;
        case '*': token.type = (*lexer->current == '=') ? (lexer->current++, lexer->column++, TStarAssign) : ((*lexer->current == '*') ? (lexer->current++, lexer->column++, TPower) : TStar); break;
        case '/': token.type = (*lexer->current == '=') ? (lexer->current++, lexer->column++, TSlashAssign) : TSlash; break;
        case '!': token.type = (*lexer->current == '=') ? (lexer->current++, lexer->column++, TNotEqual) : TNot; break;
        case '=': token.type = (*lexer->current == '=') ? (lexer->current++, lexer->column++, TEqual) : TAssign; break;
        case '&': token.type = (*lexer->current == '&') ? (lexer->current++, lexer->column++, TLogicalAnd) : TAmpersand; break;
        case '|': token.type = (*lexer->current == '|') ? (lexer->current++, lexer->column++, TLogicalOr) : TPipe; break;
        case '>': token.type = (*lexer->current == '=') ? (lexer->current++, lexer->column++, TGreaterEqual) : ((*lexer->current == '>') ? (lexer->current++, lexer->column++, TRightShift) : TGreater); break;
        case '<': token.type = (*lexer->current == '=') ? (lexer->current++, lexer->column++, TLessEqual) : ((*lexer->current == '<') ? (lexer->current++, lexer->column++, TLeftShift) : TLess); break;

        case '"': {
            while (*lexer->current != '"' && *lexer->current != '\0') {
                lexer->current++;
                lexer->column++;
            }
            if (*lexer->current == '"') {
                lexer->current++;
                lexer->column++;
                token.type = TStringLiteral;
                token.length = (int)(lexer->current - lexer->current + 1);
            } else {
                error(LexicalError, "Unterminated string literal", &token);
                token.type = TError;
            }
            return token;
        }

        case '\'': {
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
                token.length = (int)(lexer->current - lexer->current + 1);
            } else {
                error(LexicalError, "Unterminated character literal", &token);
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
                token.type = checkKeyword(start, (size_t)(lexer->current - start));
                token.length = (int)(lexer->current - start);
                return token;
            }

            if (isdigit(c)) {
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
                token.length = (int)(lexer->current - lexer->current - 1);
                return token;
            }

            error(LexicalError, "Unexpected character", &token);
            token.type = TError;

            while (!isspace(*lexer->current) && *lexer->current != '\0') {
                lexer->current++;
                lexer->column++;
            }
            break;
    }

    token.length = (int)(lexer->current - token.start);
    return token;
}

void skipWhitespace(Lexer *lexer) {
    while (isspace(*lexer->current) || *lexer->current == '#') {
        lexer->column = (*lexer->current == '\n') ? 1 : lexer->column + 1;
        lexer->line += (*lexer->current == '\n');
        lexer->current++;
    }
}
