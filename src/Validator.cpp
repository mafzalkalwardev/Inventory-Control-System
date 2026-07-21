#include "Validator.h"
#include <iostream>
#include <limits>

void Validator::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool Validator::readInt(const std::string& prompt, int& value, int minValue, int maxValue) {
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInput();
            if (value >= minValue && value <= maxValue) {
                return true;
            }
            std::cout << "Value must be between " << minValue << " and " << maxValue << ".\n";
        } else {
            clearInput();
            std::cout << "Invalid integer. Please try again.\n";
        }
    }
}

bool Validator::readDouble(const std::string& prompt, double& value, double minValue) {
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInput();
            if (value >= minValue) {
                return true;
            }
            std::cout << "Value must be at least " << minValue << ".\n";
        } else {
            clearInput();
            std::cout << "Invalid number. Please try again.\n";
        }
    }
}

bool Validator::readNonEmptyString(const std::string& prompt,
                                   std::string& value,
                                   std::size_t maxLen) {
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, value)) {
            clearInput();
            continue;
        }

        // Trim leading/trailing spaces
        const auto start = value.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) {
            std::cout << "Input cannot be empty.\n";
            continue;
        }
        const auto end = value.find_last_not_of(" \t\r\n");
        value = value.substr(start, end - start + 1);

        if (value.empty()) {
            std::cout << "Input cannot be empty.\n";
            continue;
        }
        if (value.size() > maxLen) {
            std::cout << "Input too long (max " << maxLen << " characters).\n";
            continue;
        }
        return true;
    }
}
