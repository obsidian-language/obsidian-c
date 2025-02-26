#ifndef COLOR_H
#define COLOR_H

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
    #define BLUE    "\x1b[0;34m"
    #define BLACK   "\x1b[1;30m"
    #define GRAY    "\x1b[1;90m"
    #define RESET   "\x1b[0m"
#endif

#endif // COLOR_H
