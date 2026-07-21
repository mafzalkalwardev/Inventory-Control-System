#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "HashTable.h"
#include <string>

class FileHandler {
public:
    static bool saveInventory(const HashTable& table, const std::string& path);
    static bool loadInventory(HashTable& table, const std::string& path);

    static bool ensureUsersFile(const std::string& path);
    static bool authenticate(const std::string& path,
                             const std::string& username,
                             const std::string& password);
};

#endif
