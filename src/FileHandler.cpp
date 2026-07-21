#include "FileHandler.h"
#include <fstream>
#include <iostream>

bool FileHandler::saveInventory(const HashTable& table, const std::string& path) {
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    if (!out) {
        std::cerr << "Error: Unable to open inventory file for writing: " << path << '\n';
        return false;
    }

    const int count = table.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    if (!out) {
        return false;
    }

    bool ok = true;
    table.forEach([&out, &ok](const Product& product) {
        out.write(reinterpret_cast<const char*>(&product), sizeof(Product));
        if (!out) {
            ok = false;
        }
    });

    return ok;
}

bool FileHandler::loadInventory(HashTable& table, const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        // First run: no file yet — treat as empty inventory
        return true;
    }

    int count = 0;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (!in || count < 0) {
        std::cerr << "Error: Inventory file is corrupt or unreadable.\n";
        return false;
    }

    table.clear();
    for (int i = 0; i < count; ++i) {
        Product product;
        in.read(reinterpret_cast<char*>(&product), sizeof(Product));
        if (!in) {
            std::cerr << "Error: Failed while reading product records.\n";
            return false;
        }
        if (!table.insert(product)) {
            std::cerr << "Warning: Duplicate product ID " << product.productId
                      << " skipped during load.\n";
        }
    }
    return true;
}

bool FileHandler::ensureUsersFile(const std::string& path) {
    std::ifstream check(path);
    if (check.good()) {
        return true;
    }
    check.close();

    std::ofstream out(path);
    if (!out) {
        std::cerr << "Error: Unable to create users file: " << path << '\n';
        return false;
    }

    // Default coursework credentials (plaintext by design for this project)
    out << "admin admin123\n";
    return static_cast<bool>(out);
}

bool FileHandler::authenticate(const std::string& path,
                               const std::string& username,
                               const std::string& password) {
    std::ifstream in(path);
    if (!in) {
        return false;
    }

    std::string storedUser;
    std::string storedPass;
    while (in >> storedUser >> storedPass) {
        if (storedUser == username && storedPass == password) {
            return true;
        }
    }
    return false;
}
