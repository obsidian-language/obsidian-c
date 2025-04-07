#ifndef ERROR_H
#define ERROR_H

/**
 * @file error.h
 * @brief Defines error types and functions for error handling in the Obsidian compiler.
 *
 * This header file provides the definitions for various error types that can occur 
 * during the compilation process, as well as functions for converting error types 
 * to strings and reporting errors.
 * 
 * @author Codezz-ops <codezz-ops@obsidian.cc>
 * 
 * @copyright Copyright (c) 2024 Obsidian Language
 * @license BSD 3-Clause
 */

#include "lexer.h"

/**
 * @enum ErrorType
 * @brief Enumeration of error types for the Obsidian compiler.
 *
 * This enumeration defines the different types of errors that can be encountered 
 * during the compilation process.
 */
typedef enum {
    LexicalError,
    SyntaxError,
    SemanticError
} ErrorType;

/**
 * @brief Converts an ErrorType to its corresponding string representation.
 * 
 * This function takes an ErrorType and returns a string that describes the error type.
 * 
 * @param type The ErrorType to convert.
 * @return const char* A string representation of the error type.
 */
const char* errorTypeToString(ErrorType type);

/**
 * @brief Reports an error with a specific message and token information.
 * 
 * This function handles error reporting by displaying the error message and 
 * associated token information.
 * 
 * @param type The type of error being reported.
 * @param message The error message to display.
 * @param token Pointer to the token associated with the error (if applicable).
 * @return int Returns 0 on success, or a non-zero error code on failure.
 */
int error(ErrorType type, const char *message, Token *token);

#endif // ERROR_H
