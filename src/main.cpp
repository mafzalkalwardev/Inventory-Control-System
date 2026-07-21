#include "InventorySystem.h"
#include "Utils.h"
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace {
std::string resolveDataPath(const std::string& filename) {
    // Prefer ./data next to cwd (typical when running from build/)
    const fs::path local = fs::path("data") / filename;
    if (fs::exists(local) || fs::exists("data")) {
        return local.string();
    }

    // Fallback: ../data when launched from a nested build folder
    const fs::path parent = fs::path("..") / "data" / filename;
    return parent.string();
}

void ensureDataDirectory() {
    std::error_code ec;
    fs::create_directories("data", ec);
}
}  // namespace

int main() {
    ensureDataDirectory();

    const std::string inventoryPath = resolveDataPath("inventory.dat");
    const std::string usersPath = resolveDataPath("users.dat");

    InventorySystem system(inventoryPath, usersPath);

    Utils::clearScreen();
    Utils::printBanner("Inventory Control System Using Hashing and DBMS");
    std::cout << "  Data Structures (C++) Project\n"
              << "  Hash Table + Binary File Persistence\n";
    Utils::printLine('=', 70);
    Utils::pause();

    if (!system.login()) {
        return 1;
    }

    system.run();
    return 0;
}
