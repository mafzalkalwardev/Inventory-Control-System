#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
public:
    static void clearScreen();
    static void pause();
    static void printBanner(const std::string& title);
    static void printLine(char ch = '=', int width = 70);
    static void printHeaderRow();
};

#endif
