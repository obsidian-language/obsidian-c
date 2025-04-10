#ifndef COLOR_H
#define COLOR_H

/**
 * @file color.h
 * @brief Provides functions for setting text colors in the console.
 *
 * This header file defines the `set_color` function, which allows changing
 * the text color in the console output. It includes platform-specific 
 * implementations for Windows and ANSI escape codes for other systems.
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
 * is specified as an integer value. On Windows, it uses the Windows API
 * to set the color, while on other platforms, it uses ANSI escape codes.
 * 
 * @param color An integer representing the color to set. The valid range
 *              is platform-dependent; for Windows, it should be between
 *              0 and 255.
 */
void set_color(int color);

#ifdef _WIN32
    #include <windows.h>
    HANDLE hConsole;
    void set_color(int color) {
        if (color < 0 || color > 0xFF) return;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (WORD)color);
    }
    
#else
    #define LIGHT_GREEN   "\x1b[1;32m"
    #define LIGHT_YELLOW  "\x1b[1;33m"
    #define LIGHT_CYAN    "\x1b[1;36m"
    #define LIGHT_MAGENTA "\x1b[1;35m"
    #define LIGHT_RED     "\x1b[1;31m"
    #define LIGHT_BLUE    "\x1b[1;34m"
    #define GREEN   "\x1b[0;32m"
    #define YELLOW  "\x1b[0;33m"
    #define CYAN    "\x1b[0;36m"
    #define WHITE   "\x1b[0;37m"
    #define MAGENTA "\x1b[0;35m"
    #define RED     "\x1b[0;31m"
    #define BLUE    "\x1b[38;5;69m"
    #define BLACK   "\x1b[1;30m"
    #define GRAY    "\x1b[38;5;7m"
    #define RESET   "\x1b[0m"
#endif

#endif // COLOR_H
