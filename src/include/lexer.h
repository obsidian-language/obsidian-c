#ifndef LEXER_H
#define LEXER_H

/**
 * @file lexer.h
 * @brief Defines the lexer for the Obsidian programming language.
 *
 * This header file contains the definitions for the lexer, including token types,
 * structures for tokens and the lexer itself, and function declarations for 
 * initializing the lexer and retrieving tokens from the source code.
 * 
 * @author Codezz-ops <codezz-ops@obsidian.cc>
 * 
 * @copyright Copyright (c) 2024 Obsidian Language
 * @license BSD 3-Clause
 */

/**
 * @enum TokenKind
 * @brief Enumeration of token types recognized by the lexer.
 *
 * This enumeration defines the various token types that the lexer can recognize,
 * including operators, keywords, literals, and special tokens.
 */
#include <stddef.h>

typedef enum {
    TLparen, TRparen, TLbrace, TRbrace, TLbracket, TRbracket, TPlus, TMinus, TStar, TSlash, TDot, TColon, TSemi, TComma, TNot, TGreater, TLess, TCarot, TPercent, TAssign, TAmpersand, TPipe, TQuestion, TXorNot, TPower, TLogicalOr, TLogicalAnd, TPlusAssign, TMinusAssign, TStarAssign, TSlashAssign, TEqual, TNotEqual, TGreaterEqual, TLessEqual, TDecrement, TIncrement, TXor, TLeftShift, TRightShift, TI8, TI16, TI32, TI64, TU8, TU16, TU32, TU64, TF32, TF64, TString, TChar, TBool, TVoid, TConst, TFn, TIf, TElse, TSwitch, TCase, TDefault, TWhile, TFor, TReturn, TStruct, TEnum, TNew, TNull, TTrue, TFalse, TAlloc, TDealloc, TUnsafe, TSizeof, TPrivate, TTypeof, TImport, TExport, TCast, TPrintln, TLength, TBreak, TEof, TError, TIntLiteral, TFloatLiteral, TBoolLiteral, TStringLiteral, TCharLiteral, TIdentifier, TReturnType, TUnknown
} TokenKind;

/**
 * @struct Token
 * @brief Represents a token recognized by the lexer.
 *
 * This structure holds information about a token, including its type,
 * the starting position in the source code, its length, and its line
 * and column numbers.
 */
typedef struct {
    TokenKind type; /**< The type of the token. */
    char *start;    /**< Pointer to the start of the token in the source code. */
    int length;     /**< Length of the token. */
    int line;       /**< Line number where the token was found. */
    int column;     /**< Column number where the token was found. */
} Token;

/**
 * @struct Lexer
 * @brief Represents the lexer state.
 *
 * This structure holds the current state of the lexer, including the
 * current position in the source code and the line and column numbers.
 */
typedef struct {
    char *start, *current;
    int line, column;
} Lexer;

/**
 * @struct KeywordEntry
 * @brief Represents a keyword entry for the lexer.
 *
 * This structure holds a keyword and its corresponding token type.
 */
typedef struct {
    const char *keyword;
    TokenKind token;
} KeywordEntry;

/**
 * @brief Initializes the lexer with the source code.
 * 
 * This function sets the starting position, current position, line number,
 * and column number for the lexer based on the provided source code.
 * 
 * @param lexer Pointer to the lexer instance to initialize.
 * @param source Pointer to the source code string.
 */
void initLexer(Lexer *lexer, char *source);

/**
 * @brief Retrieves the next token from the lexer.
 * 
 * This function analyzes the source code and returns the next token
 * recognized by the lexer.
 * 
 * @param lexer Pointer to the lexer instance.
 * @return Token The next token recognized by the lexer.
 */
Token getNextToken(Lexer *lexer);

/**
 * @brief Skips whitespace and comments in the source code.
 * 
 * This function advances the lexer's current position, skipping over
 * any whitespace characters or comments found in the source code.
 * 
 * @param lexer Pointer to the lexer instance.
 */
void skipWhitespace(Lexer *lexer);

/**
 * @brief Compares two keyword entries for sorting and searching.
 * 
 * This function is used by qsort and bsearch to compare two keyword
 * entries based on their keyword strings.
 * 
 * @param a Pointer to the first keyword entry.
 * @param b Pointer to the second keyword entry.
 * @return int Result of the comparison.
 */
int compareKeywords(const void *a, const void *b);

/**
 * @brief Sorts the keywords array if it hasn't been sorted yet.
 * 
 * This function sorts the array of keyword entries to prepare for
 * binary search operations.
 */
void sortKeywords(void);

/**
 * @brief Checks if a given string is a keyword.
 * 
 * This function compares the provided string against a list of known
 * keywords and returns the corresponding token type.
 * 
 * @param start Pointer to the start of the keyword string.
 * @param length Length of the keyword string.
 * @return TokenKind The token type corresponding to the keyword or TIdentifier if not found.
 */
TokenKind checkKeyword(const char *start, size_t length);

#endif // LEXER_H
