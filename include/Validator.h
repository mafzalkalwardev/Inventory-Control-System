#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

class Validator {
public:
    static bool readInt(const std::string& prompt, int& value, int minValue, int maxValue);
    static bool readDouble(const std::string& prompt, double& value, double minValue);
    static bool readNonEmptyString(const std::string& prompt, std::string& value, std::size_t maxLen);
    static void clearInput();
};

#endif
