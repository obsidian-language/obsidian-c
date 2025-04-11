#ifndef COLOR_H
#define COLOR_H

/**
 * @file color.h
 * @brief Provides functions for setting text colors in the console.
 *
 * This header file defines the `set_color` function, which allows changing
 * the text color in the console output. It includes implementations in 
 * ANSI escape codes for systems.
 *
 * @author Codezz-ops <codezz-ops@obsidian.cc>
 * 
 * @copyright Copyright (c) 2024 Obsidian Language
 * @license BSD 3-Clause
 */

/**
 * @brief Sets the console text color.
 * 
 * This function changes the text color of the console output. The color
 * is specified as an integer value. it uses ANSI escape codes.
 * 
 * @param color An integer representing the color to set. The valid range
 *              is platform-dependent; for Windows, it should be between
 *              0 and 255.
 */
#define LIGHT_GREEN   "\x1b[1;32m"
#define LIGHT_YELLOW  "\x1b[1;33m"
#define LIGHT_CYAN    "\x1b[1;36m"
#define LIGHT_MAGENTA "\x1b[1;35m"
#define LIGHT_RED     "\x1b[38;2;217;114;131m"
#define LIGHT_BLUE    "\x1b[1;34m"
#define GREEN   "\x1b[38;2;112;191;177m"
#define YELLOW  "\x1b[38;2;200;159;101m"
#define CYAN    "\x1b[0;36m"
#define WHITE   "\x1b[0;37m"
#define MAGENTA "\x1b[38;2;170;142;212m"
#define RED     "\x1b[0;31m"
#define BLUE    "\x1b[38;2;118;148;212m"
#define BLACK   "\x1b[1;30m"
#define GRAY    "\x1b[38;5;7m"
#define RESET   "\x1b[0m"

#endif // COLOR_H
