#include "include/lexer.h"
#include "include/error.h"
#include <ctype.h>
#include <string.h>

const char *keywords[] = {
    "if", "else", "while", "for", "return", "int", "float", "char", "void", "const", "fn", "switch", "case", "default", "struct", "enum", "new", "null", "true", "false", "alloc", "dealloc", "unsafe", "sizeof", "private", "typeof", "import", "export", "cast", "println", "length", "break", "int", "float", "string", "char", "bool", "void"
};

void initLexer(Lexer *lexer, char *source) {
    lexer->start = source;
    lexer->current = source;
    lexer->line = 1;
    lexer->column = 1;
}

TokenKind checkKeyword(const char *start, int length) {
    for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strncmp(start, keywords[i], length) == 0 && keywords[i][length] == '\0') {
            if (strcmp(keywords[i], "if") == 0) return If;
            if (strcmp(keywords[i], "else") == 0) return Else;
            if (strcmp(keywords[i], "while") == 0) return While;
            if (strcmp(keywords[i], "for") == 0) return For;
            if (strcmp(keywords[i], "return") == 0) return Return;
            if (strcmp(keywords[i], "char") == 0) return Char;
            if (strcmp(keywords[i], "void") == 0) return Void;
            if (strcmp(keywords[i], "const") == 0) return Const;
            if (strcmp(keywords[i], "fn") == 0) return Fn;
            if (strcmp(keywords[i], "switch") == 0) return Switch;
            if (strcmp(keywords[i], "case") == 0) return Case;
            if (strcmp(keywords[i], "default") == 0) return Default;
            if (strcmp(keywords[i], "struct") == 0) return Struct;
            if (strcmp(keywords[i], "enum") == 0) return Enum;
            if (strcmp(keywords[i], "new") == 0) return New;
            if (strcmp(keywords[i], "null") == 0) return Null;
            if (strcmp(keywords[i], "true") == 0) return True;
            if (strcmp(keywords[i], "false") == 0) return False;
            if (strcmp(keywords[i], "alloc") == 0) return Alloc;
            if (strcmp(keywords[i], "dealloc") == 0) return Dealloc;
            if (strcmp(keywords[i], "unsafe") == 0) return Unsafe;
            if (strcmp(keywords[i], "sizeof") == 0) return Sizeof;
            if (strcmp(keywords[i], "private") == 0) return Private;
            if (strcmp(keywords[i], "typeof") == 0) return Typeof;
            if (strcmp(keywords[i], "import") == 0) return Import;
            if (strcmp(keywords[i], "export") == 0) return Export;
            if (strcmp(keywords[i], "cast") == 0) return Cast;
            if (strcmp(keywords[i], "println") == 0) return Println;
            if (strcmp(keywords[i], "length") == 0) return Length;
            if (strcmp(keywords[i], "break") == 0) return Break;
            if (strcmp(keywords[i], "i8") == 0) return I8;
            if (strcmp(keywords[i], "i16") == 0) return I16;
            if (strcmp(keywords[i], "i32") == 0) return I32;
            if (strcmp(keywords[i], "i64") == 0) return I64;
            if (strcmp(keywords[i], "f32") == 0) return F32;
            if (strcmp(keywords[i], "f64") == 0) return F64;
            if (strcmp(keywords[i], "u8") == 0) return U8;
            if (strcmp(keywords[i], "u16") == 0) return U16;
            if (strcmp(keywords[i], "u32") == 0) return U32;
            if (strcmp(keywords[i], "u64") == 0) return U64;
            if (strcmp(keywords[i], "string") == 0) return String;
            if (strcmp(keywords[i], "char") == 0) return Char;
            if (strcmp(keywords[i], "bool") == 0) return Bool;
            if (strcmp(keywords[i], "void") == 0) return Void;
        }
    }

    return Identifier;
}

Token getNextToken(Lexer *lexer) {
    skipWhitespace(lexer);

    Token token;
    token.start = lexer->current;
    token.line = lexer->line;
    token.column = lexer->column;

    switch (*lexer->current) {
        case '(': token.type = Lparen; lexer->current++; lexer->column++; break;
        case ')': token.type = Rparen; lexer->current++; lexer->column++; break;
        case '{': token.type = Lbrace; lexer->current++; lexer->column++; break;
        case '}': token.type = Rbrace; lexer->current++; lexer->column++; break;
        case '[': token.type = Lbracket; lexer->current++; lexer->column++; break;
        case ']': token.type = Rbracket; lexer->current++; lexer->column++; break;
        case '+':
            lexer->current++;
            lexer->column++;
            if (*lexer->current == '+') {
                lexer->current++;
                lexer->column++;
                token.type = Increment;
            } else if (*lexer->current == '=') {
                lexer->current++;
                lexer->column++;
                token.type = PlusAssign;
            } else {
                token.type = Plus;
            }
            break;
        case '-':
            lexer->current++;
            lexer->column++;
            if (*lexer->current == '-') {
                lexer->current++;
                lexer->column++;
                token.type = Decrement;
            } else if (*lexer->current == '=') {
                lexer->current++;
                lexer->column++;
                token.type = MinusAssign;
            } else {
                token.type = Minus;
            }
            break;
        case '*':
            lexer->current++;
            lexer->column++;
            if (*lexer->current == '=') {
                lexer->current++;
                lexer->column++;
                token.type = StarAssign;
            } else {
                token.type = Star;
            }
            break;
        case '/':
            lexer->current++;
            lexer->column++;
            if (*lexer->current == '=') {
                lexer->current++;
                lexer->column++;
                token.type = SlashAssign;
            } else {
                token.type = Slash;
            }
            break;
        case '.': token.type = Dot; lexer->current++; lexer->column++; break;
        case ':': token.type = Colon; lexer->current++; lexer->column++; break;
        case ';': token.type = Semi; lexer->current++; lexer->column++; break;
        case ',': token.type = Comma; lexer->current++; lexer->column++; break;
        case '!':
            lexer->current++;
            lexer->column++;
            if (*lexer->current == '=') {
                lexer->current++;
                lexer->column++;
                token.type = NotEqual;
            } else {
                token.type = Not;
            }
            break;
        case '>':
            lexer->current++;
            lexer->column++;
            if (*lexer->current == '=') {
                lexer->current++;
                lexer->column++;
                token.type = GreaterEqual;
            } else if (*lexer->current == '>') {
                lexer->current++;
                lexer->column++;
                token.type = RightShift;
            } else {
                token.type = Greater;
            }
            break;
        case '<':
            lexer->current++;
            lexer->column++;
            if (*lexer->current == '=') {
                lexer->current++;
                lexer->column++;
                token.type = LessEqual;
            } else if (*lexer->current == '<') {
                lexer->current++;
                lexer->column++;
                token.type = LeftShift;
            } else {
                token.type = Less;
            }
            break;
        case '=':
            lexer->current++;
            lexer->column++;
            if (*lexer->current == '=') {
                lexer->current++;
                lexer->column++;
                token.type = Equal;
            } else {
                token.type = Assign;
            }
            break;
        case '&':
            lexer->current++;
            lexer->column++;
            if (*lexer->current == '&') {
                lexer->current++;
                lexer->column++;
                token.type = LogicalAnd;
            } else {
                token.type = Ampersand;
            }
            break;
        case '|':
            lexer->current++;
            lexer->column++;
            if (*lexer->current == '|') {
                lexer->current++;
                lexer->column++;
                token.type = LogicalOr;
            } else {
                token.type = Pipe;
            }
            break;
        case '"':
            lexer->current++;
            lexer->column++;
            while (*lexer->current != '"' && *lexer->current != '\0') {
                lexer->current++;
                lexer->column++;
            }
            if (*lexer->current == '"') {
                lexer->current++;
                lexer->column++;
            } else {
                token.length = 1;
                error("Unterminated string literal", &token);
            }
            token.type = StringLiteral;
            token.length = lexer->current - token.start;
            return token;
        case '\0': token.type = Eof; break;
        case '\'':
            lexer->current++;
            lexer->column++;
            if (*lexer->current == '\\') {
                lexer->current++;
                lexer->column++;
            }
            lexer->current++;
            lexer->column++;
            if (*lexer->current == '\'') {
                lexer->current++;
                lexer->column++;
            } else {
                token.length = 1;
                error("Unterminated character literal", &token);
            }
            token.type = CharLiteral;
            token.length = lexer->current - token.start;
            return token;
        default:
            if (isalpha(*lexer->current)) { 
                const char *start = lexer->current;
                while (isalnum(*lexer->current)) {
                    lexer->current++;
                    lexer->column++;
                }
                int length = lexer->current - start;
                token.type = checkKeyword(start, length);
                token.length = length;
                return token;
            } else if (isdigit(*lexer->current)) {
                const char *start = lexer->current;
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
            } else {
                token.length = 1;
                error("Unexpected character", &token);
            }
            break;
    }

    token.length = lexer->current - token.start;
    return token;
}

int isEndOfFile(Lexer *lexer) {
    return *lexer->current == '\0';
}

void skipWhitespace(Lexer *lexer) {
    while (isspace(*lexer->current)) {
        if (*lexer->current == '\n') {
            lexer->line++;
            lexer->column = 1;
        } else {
            lexer->column++;
        }
        lexer->current++;
    }
}