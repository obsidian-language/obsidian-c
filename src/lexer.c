#include "include/lexer.h"
#include "include/error.h"
#include <ctype.h>
#include <string.h>

#define KEYWORD_COUNT (sizeof(keywords) / sizeof(keywords[0]))

static const KeywordEntry keywords[] = {
    {"if", If}, {"else", Else}, {"while", While}, {"for", For}, {"return", Return}, {"const", Const},
    {"fn", Fn}, {"switch", Switch}, {"case", Case}, {"default", Default}, {"struct", Struct},
    {"enum", Enum}, {"new", New}, {"null", Null}, {"true", True}, {"false", False},
    {"alloc", Alloc}, {"dealloc", Dealloc}, {"unsafe", Unsafe}, {"sizeof", Sizeof},
    {"private", Private}, {"typeof", Typeof}, {"import", Import}, {"export", Export},
    {"cast", Cast}, {"println", Println}, {"length", Length}, {"break", Break},
    {"i8", I8}, {"i16", I16}, {"i32", I32}, {"i64", I64}, {"f32", F32}, {"f64", F64},
    {"u8", U8}, {"u16", U16}, {"u32", U32}, {"u64", U64}, {"string", String}, {"bool", Bool}, {"void", Void}, {"char", Char}
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
    return Identifier;
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
        case '(': token.type = Lparen;   break;
        case ')': token.type = Rparen;   break;
        case '{': token.type = Lbrace;   break;
        case '}': token.type = Rbrace;   break;
        case '[': token.type = Lbracket; break;
        case ']': token.type = Rbracket; break;
        case '.': token.type = Dot;      break;
        case ':': token.type = Colon;    break;
        case ';': token.type = Semi;     break;
        case ',': token.type = Comma;    break;
        case '+': token.type = matchNext('+', Increment, matchNext('=', PlusAssign, Plus)); break;
        case '-': token.type = matchNext('-', Decrement, matchNext('=', MinusAssign, Minus)); break;
        case '*': token.type = matchNext('=', StarAssign, Star); break;
        case '/': token.type = matchNext('=', SlashAssign, Slash); break;
        case '!': token.type = matchNext('=', NotEqual, Not); break;
        case '=': token.type = matchNext('=', Equal, Assign); break;
        case '&': token.type = matchNext('&', LogicalAnd, Ampersand); break;
        case '|': token.type = matchNext('|', LogicalOr, Pipe); break;
        case '>': 
            token.type = matchNext('=', GreaterEqual, matchNext('>', RightShift, Greater));
            break;
        case '<': 
            token.type = matchNext('=', LessEqual, matchNext('<', LeftShift, Less));
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
                token.type = StringLiteral;
                token.length = lexer->current - start + 1;
            } else {
                error("Unterminated string literal", &token);
                token.type = Error;
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
                token.type = CharLiteral;
                token.length = lexer->current - start + 1;
            } else {
                error("Unterminated character literal", &token);
                token.type = Error;
            }
            return token;
        }

        case '\0': token.type = Eof; break;

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
                    token.type = FloatLiteral;
                } else {
                    token.type = IntLiteral;
                }
                token.length = lexer->current - start;
                return token;
            }

            error("Unexpected character", &token);
            token.type = Error;
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