/**
 * @file lexer.c
 * @brief Implements the lexer for the Obsidian programming language.
 *
 * This file is responsible for tokenizing the source code into meaningful
 * symbols for further processing. It handles various language constructs and
 * keywords, ensuring accurate parsing and syntax analysis.
 *
 * @author Codezz-ops <codezz-ops@obsidian.cc>
 *
 * @copyright Copyright (c) 2024 Obsidian Language
 * @license BSD 3-Clause
 */

#include "include/error.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Array of keyword entries for the lexer.
 */
static KeywordEntry keywords[] = {
    {"alloc", TAlloc},     {"break", TBreak},     {"case", TCase},
    {"char", TChar},       {"const", TConst},     {"dealloc", TDealloc},
    {"default", TDefault}, {"else", TElse},       {"enum", TEnum},
    {"export", TExport},   {"false", TFalse},     {"fn", TFn},
    {"for", TFor},         {"if", TIf},           {"import", TImport},
    {"i8", TI8},           {"i16", TI16},         {"i32", TI32},
    {"i64", TI64},         {"f32", TF32},         {"f64", TF64},
    {"length", TLength},   {"new", TNew},         {"null", TNull},
    {"private", TPrivate}, {"println", TPrintln}, {"return", TReturn},
    {"sizeof", TSizeof},   {"string", TString},   {"struct", TStruct},
    {"switch", TSwitch},   {"true", TTrue},       {"typeOf", TTypeof},
    {"unsafe", TUnsafe},   {"u8", TU8},           {"u16", TU16},
    {"u32", TU32},         {"u64", TU64},         {"void", TVoid},
    {"while", TWhile}};

/**
 * @brief Compares two keyword entries for qsort and bsearch.
 *
 * This function is used to compare two keyword entries based on their keyword
 * strings. It is utilized by the qsort and bsearch functions to sort and search
 * the keywords array.
 *
 * @param a Pointer to the first keyword entry.
 * @param b Pointer to the second keyword entry.
 * @return int Result of the comparison: negative if a < b, zero if a == b,
 * positive if a > b.
 */
int compareKeywords(const void *a, const void *b) {
  return strcmp(((KeywordEntry *)a)->keyword, ((KeywordEntry *)b)->keyword);
}

/**
 * @brief Sorts the keywords array if it hasn't been sorted yet.
 *
 * This function uses the qsort function to sort the keywords array based on the
 * keyword strings. It ensures that the keywords are sorted only once to
 * optimize subsequent searches.
 */
void sortKeywords(void) {
  static int sorted = 0;
  if (!sorted) {
    qsort(keywords, sizeof(keywords) / sizeof(keywords[0]),
          sizeof(KeywordEntry), compareKeywords);
    sorted = 1;
  }
}

/**
 * @brief Initializes the lexer with the source code.
 *
 * @param lexer Pointer to the lexer instance.
 * @param source Pointer to the source code string.
 */
void initLexer(Lexer *lexer, char *source) {
  lexer->start = source;
  lexer->current = source;
  lexer->line = 1;
  lexer->column = 1;
}

/**
 * @brief Checks if a given string is a keyword.
 *
 * This function compares the provided string against a list of known keywords
 * and returns the corresponding token type. It sorts the keywords if they
 * haven't been sorted yet.
 *
 * @param start Pointer to the start of the keyword string.
 * @param length Length of the keyword string.
 * @return TokenKind The token kind corresponding to the keyword or TIdentifier
 * if not found.
 */
TokenKind checkKeyword(const char *start, size_t length) {
  sortKeywords();
  char keyword[32];
  size_t keywordsCount;
  KeywordEntry *result;

  if (length >= sizeof(keyword))
    return TIdentifier;
  memcpy(keyword, start, length); ///< Copy the keyword from the source.
  keyword[length] = '\0';

  KeywordEntry key = {.keyword = keyword};

  keywordsCount = sizeof(keywords) / sizeof(keywords[0]);
  result = bsearch(&key, keywords, keywordsCount, sizeof(KeywordEntry),
                   compareKeywords);

  return result ? result->token : TIdentifier;
}

/**
 * @brief Retrieves the next token from the lexer.
 *
 * This function analyzes the source code and returns the next token recognized
 * by the lexer. It handles different types of tokens, including operators,
 * keywords, literals, and special characters.
 *
 * @param lexer Pointer to the lexer instance.
 * @return Token The next token recognized by the lexer.
 */
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
  case '(':
    token.type = TLparen;
    break;
  case ')':
    token.type = TRparen;
    break;
  case '{':
    token.type = TLbrace;
    break;
  case '}':
    token.type = TRbrace;
    break;
  case '[':
    token.type = TLbracket;
    break;
  case ']':
    token.type = TRbracket;
    break;
  case '.':
    token.type = TDot;
    break;
  case ':':
    token.type = TColon;
    break;
  case ';':
    token.type = TSemi;
    break;
  case ',':
    token.type = TComma;
    break;
  case '?':
    token.type = TQuestion;
    break;
  case '%':
    token.type = TPercent;
    break;
  case '~':
    token.type = TXorNot;
    break;
  case '^':
    token.type = (*lexer->current == '^')
                     ? (lexer->current++, lexer->column++, TXor)
                     : TCarot;
    break;
  case '+':
    token.type = (*lexer->current == '+')
                     ? (lexer->current++, lexer->column++, TIncrement)
                     : ((*lexer->current == '=')
                            ? (lexer->current++, lexer->column++, TPlusAssign)
                            : TPlus);
    break;
  case '-':
    token.type = (*lexer->current == '-')
                     ? (lexer->current++, lexer->column++, TDecrement)
                     : ((*lexer->current == '=')
                            ? (lexer->current++, lexer->column++, TMinusAssign)
                            : TMinus);
    break;
  case '*':
    token.type = (*lexer->current == '=')
                     ? (lexer->current++, lexer->column++, TStarAssign)
                     : ((*lexer->current == '*')
                            ? (lexer->current++, lexer->column++, TPower)
                            : TStar);
    break;
  case '/':
    token.type = (*lexer->current == '=')
                     ? (lexer->current++, lexer->column++, TSlashAssign)
                     : TSlash;
    break;
  case '!':
    token.type = (*lexer->current == '=')
                     ? (lexer->current++, lexer->column++, TNotEqual)
                     : TNot;
    break;
  case '=':
    token.type = (*lexer->current == '=')
                     ? (lexer->current++, lexer->column++, TEqual)
                     : TAssign;
    break;
  case '&':
    token.type = (*lexer->current == '&')
                     ? (lexer->current++, lexer->column++, TLogicalAnd)
                     : TAmpersand;
    break;
  case '|':
    token.type = (*lexer->current == '|')
                     ? (lexer->current++, lexer->column++, TLogicalOr)
                     : TPipe;
    break;
  case '>':
    token.type = (*lexer->current == '=')
                     ? (lexer->current++, lexer->column++, TGreaterEqual)
                     : ((*lexer->current == '>')
                            ? (lexer->current++, lexer->column++, TRightShift)
                            : TGreater);
    break;
  case '<':
    token.type = (*lexer->current == '=')
                     ? (lexer->current++, lexer->column++, TLessEqual)
                     : ((*lexer->current == '<')
                            ? (lexer->current++, lexer->column++, TLeftShift)
                            : TLess);
    break;

  case '"': {
    while (*lexer->current != '"' && *lexer->current != '\0') {
      lexer->current++;
      lexer->column++;
    }
    if (*lexer->current == '"') {
      lexer->current++;
      lexer->column++;
      token.type = TStringLiteral;
      token.length = (int)(lexer->current - token.start);
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
      token.length = (int)(lexer->current - token.start);
    } else {
      error(LexicalError, "Unterminated character literal", &token);
      token.type = TError;
    }
    return token;
  }

  case '\0':
    token.type = TEof;
    break;

  default:
    if (isalpha(c) || c == '_') {
      const char *start = lexer->current - 1;
      while (isalnum(*lexer->current) || *lexer->current == '_') {
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

/**
 * @brief Skips whitespace and comments in the source code.
 *
 * This function advances the lexer’s current position, skipping over
 * any whitespace characters or comments found in the source code.
 *
 * @param lexer Pointer to the lexer instance.
 */
void skipWhitespace(Lexer *lexer) {
  while (isspace(*lexer->current) || *lexer->current == '#') {
    lexer->column = (*lexer->current == '\n') ? 1 : lexer->column + 1;
    lexer->line += (*lexer->current == '\n');
    lexer->current++;
  }
}
