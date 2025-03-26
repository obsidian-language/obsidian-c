#include <assert.h>
#include <string.h>
#include "include/lexer_tests.h"
#include "../src/include/lexer.h"

void test_identifier(void) {
    Lexer lexer;
    Token token;
    const char *identifiers[] = { "variable", "myVar", "test123", "another_var", "x", "y", "z", "longIdentifierName", "short", "temp", "_start", "snake_case_var", "my_long_variable_name", "_", "___", "number_123", "UPPER_SNAKE_CASE", "mixed_Snake_Case_123" };
    size_t numIdentifiers = sizeof(identifiers) / sizeof(identifiers[0]);

    for (size_t i = 0; i < numIdentifiers; ++i) {
        const char *input = identifiers[i];
        initLexer(&lexer, (char *)input);
        token = getNextToken(&lexer);

        assert(token.type == TIdentifier);
        assert(strncmp(token.start, input, strlen(input)) == 0);

        token = getNextToken(&lexer);
        assert(token.type == TEof);
    }
}

void test_keyword(void) {
    Lexer lexer;
    Token token;
    const char *input;
    const char *keywords[] = { "alloc", "break", "case", "char", "const", "dealloc", "default", "else", "enum", "export", "false", "fn", "for", "if", "import", "i8", "i16", "i32", "i64", "f32", "f64", "length", "new", "null", "private", "println", "return", "sizeof", "string", "struct", "switch", "true", "typeOf", "unsafe", "u8", "u16", "u32", "u64", "void", "while" };
    TokenKind expectedTokens[] = { TAlloc, TBreak, TCase, TChar, TConst, TDealloc, TDefault, TElse, TEnum, TExport, TFalse, TFn, TFor, TIf, TImport, TI8, TI16, TI32, TI64, TF32, TF64, TLength, TNew, TNull, TPrivate, TPrintln, TReturn, TSizeof, TString, TStruct, TSwitch, TTrue, TTypeof, TUnsafe, TU8, TU16, TU32, TU64, TVoid, TWhile };
    size_t numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (size_t i = 0; i < numKeywords; ++i) {
        input = keywords[i];
        initLexer(&lexer, (char *)input);
        token = getNextToken(&lexer);

        assert(token.type == expectedTokens[i]);
        assert(strncmp(token.start, input, strlen(input)) == 0);

        token = getNextToken(&lexer);
        assert(token.type == TEof);
    }
}

void test_numbers(void) {
    Lexer lexer;
    Token token;
    const char *inputs[] = {"123", "12.3", "0", "0.0", "456", "78.90", "0.123", "123.0"};
    TokenKind expectedTokens[] = {TIntLiteral, TFloatLiteral, TIntLiteral, TFloatLiteral, TIntLiteral, TFloatLiteral, TFloatLiteral, TFloatLiteral};
    size_t numInputs = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < numInputs; ++i) {
        const char *input = inputs[i];
        initLexer(&lexer, (char *)input);
        token = getNextToken(&lexer);

        assert(token.type == expectedTokens[i]);
        assert(strcmp(token.start, input) == 0);

        token = getNextToken(&lexer);
        assert(token.type == TEof);
    }
}

void test_operator(void) {
    Lexer lexer;
    Token token;
    const char *inputs[] = {"(", ")", "{", "}", "[", "]", ".", ":", ";", ",", "?", "%", "~", "^", "^^", "+", "+=", "-", "-=", "*", "*=", "/", "/=", "!", "!=", "=", "==", "&", "&&", "|", "||", ">", ">>", ">=", "<", "<<", "<="};
    TokenKind expectedTokens[] = {TLparen, TRparen, TLbrace, TRbrace, TLbracket, TRbracket, TDot, TColon, TSemi, TComma, TQuestion, TPercent, TXorNot, TCarot, TXor, TPlus, TPlusAssign, TMinus, TMinusAssign, TStar, TStarAssign, TSlash, TSlashAssign, TNot, TNotEqual, TAssign, TEqual, TAmpersand, TLogicalAnd, TPipe, TLogicalOr, TGreater, TRightShift, TGreaterEqual, TLess, TLeftShift, TLessEqual};
    size_t numOperators = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < numOperators; ++i) {
        const char *input = inputs[i];
        initLexer(&lexer, (char *)input);
        token = getNextToken(&lexer);

        assert(token.type == expectedTokens[i]);
        assert(strcmp(token.start, input) == 0);

        token = getNextToken(&lexer);
        assert(token.type == TEof);
    }
}

int main(void) {
    test_identifier();
    test_keyword();
    test_numbers();
    test_operator();
    return 0;
}
