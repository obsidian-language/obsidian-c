#include <assert.h>
#include <string.h>
#include "include/lexer_tests.h"
#include "../src/include/lexer.h"

void test_identifier() {
    Lexer lexer;
    Token token;
    const char *input = "variable";

    initLexer(&lexer, (char *)input);
    token = getNextToken(&lexer);
    
    assert(token.type == TIdentifier);
    assert(strcmp(token.start, "variable") == 0);
    
    token = getNextToken(&lexer);
    assert(token.type == TEof);
}

void test_keyword() {
    Lexer lexer;
    Token token;
    const char *input = "if";

    initLexer(&lexer, (char *)input);
    token = getNextToken(&lexer);

    assert(token.type == TIf);
    assert(strcmp(token.start, "if") == 0);

    token = getNextToken(&lexer);
    assert(token.type == TEof);
}

void test_numbers() {
    Lexer lexer;
    Token token;
    const char *input = "123";

    initLexer(&lexer, (char *)input);
    token = getNextToken(&lexer);

    assert(token.type == TIntLiteral);
    assert(strcmp(token.start, "123") == 0);

    token = getNextToken(&lexer);
    assert(token.type == TEof);

    input = "12.3";
    initLexer(&lexer, (char *)input);
    token = getNextToken(&lexer);

    assert(token.type == TFloatLiteral);
    assert(strcmp(token.start, "12.3") == 0);

    token = getNextToken(&lexer);
    assert(token.type == TEof);
}

void test_operator() {
    Lexer lexer;
    Token token;
    const char *input = "+";

    initLexer(&lexer, (char *)input);
    token = getNextToken(&lexer);

    assert(token.type == TPlus);
    assert(strcmp(token.start, "+") == 0);

    token = getNextToken(&lexer);
    assert(token.type == TEof);
}

int main() {
    test_identifier();
    test_keyword();
    test_numbers();
    test_operator();
    return 0;
}