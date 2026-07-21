#include "Utils.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>

void Utils::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Utils::pause() {
    std::cout << "\nPress Enter to continue..." << std::flush;
    if (!std::cin.good()) {
        std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Utils::printLine(char ch, int width) {
    for (int i = 0; i < width; ++i) {
        std::cout << ch;
    }
    std::cout << '\n';
}

void Utils::printBanner(const std::string& title) {
    printLine('=', 70);
    std::cout << "  " << title << '\n';
    printLine('=', 70);
}

void Utils::printHeaderRow() {
    std::cout << std::left
              << std::setw(8) << "ID"
              << std::setw(22) << "Name"
              << std::setw(14) << "Category"
              << std::setw(8) << "Qty"
              << std::setw(12) << "Purchase"
              << std::setw(12) << "Selling"
              << std::setw(18) << "Supplier"
              << '\n';
}
