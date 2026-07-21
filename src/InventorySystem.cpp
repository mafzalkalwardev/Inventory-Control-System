#include "InventorySystem.h"
#include "Utils.h"
#include "Validator.h"
#include <iomanip>
#include <iostream>
#include <limits>

InventorySystem::InventorySystem(const std::string& inventoryFile,
                                 const std::string& usersFile)
    : inventoryPath(inventoryFile), usersPath(usersFile), dirty(false) {}

void InventorySystem::loadData() {
    FileHandler::ensureUsersFile(usersPath);
    if (!FileHandler::loadInventory(table, inventoryPath)) {
        std::cout << "Warning: Starting with an empty inventory.\n";
    }
}

void InventorySystem::saveData() {
    if (FileHandler::saveInventory(table, inventoryPath)) {
        dirty = false;
        std::cout << "Inventory saved successfully.\n";
    } else {
        std::cout << "Error: Failed to save inventory.\n";
    }
}

bool InventorySystem::login() {
    FileHandler::ensureUsersFile(usersPath);

    Utils::clearScreen();
    Utils::printBanner("Inventory Control System - Login");
    std::cout << "Default credentials: admin / admin123\n\n";

    const int maxAttempts = 3;
    for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
        std::string username;
        std::string password;

        Validator::readNonEmptyString("Username: ", username, 32);
        Validator::readNonEmptyString("Password: ", password, 32);

        if (FileHandler::authenticate(usersPath, username, password)) {
            std::cout << "\nLogin successful. Welcome, " << username << "!\n";
            Utils::pause();
            return true;
        }

        std::cout << "Invalid username or password. "
                  << (maxAttempts - attempt) << " attempt(s) remaining.\n";
    }

    std::cout << "\nToo many failed login attempts. Exiting.\n";
    return false;
}

void InventorySystem::showMainMenu() const {
    Utils::clearScreen();
    Utils::printBanner("Inventory Control System - Main Menu");
    std::cout << "  1. Add Product\n"
              << "  2. View All Products\n"
              << "  3. Search Product (by Product ID)\n"
              << "  4. Update Product\n"
              << "  5. Delete Product\n"
              << "  6. Stock Management\n"
              << "  7. Inventory Reports\n"
              << "  8. Save Inventory\n"
              << "  9. Exit\n";
    Utils::printLine('-', 70);
    std::cout << "Products in memory: " << table.size()
              << (dirty ? "  [unsaved changes]" : "") << '\n';
}

void InventorySystem::addProduct() {
    Utils::clearScreen();
    Utils::printBanner("Add Product");

    int id = 0;
    int qty = 0;
    double purchase = 0.0;
    double selling = 0.0;
    std::string name;
    std::string category;
    std::string supplier;

    Validator::readInt("Product ID (positive integer): ", id, 1, 2000000000);
    if (table.search(id) != nullptr) {
        std::cout << "Error: Product ID " << id << " already exists.\n";
        Utils::pause();
        return;
    }

    Validator::readNonEmptyString("Product Name: ", name, Product::NAME_LEN - 1);
    Validator::readNonEmptyString("Category: ", category, Product::CATEGORY_LEN - 1);
    Validator::readInt("Quantity: ", qty, 0, 1000000000);
    Validator::readDouble("Purchase Price: ", purchase, 0.0);
    Validator::readDouble("Selling Price: ", selling, 0.0);
    Validator::readNonEmptyString("Supplier Name: ", supplier, Product::SUPPLIER_LEN - 1);

    Product product(id, name, category, qty, purchase, selling, supplier);
    if (table.insert(product)) {
        dirty = true;
        saveData();
        std::cout << "Product added successfully.\n";
    } else {
        std::cout << "Error: Failed to add product.\n";
    }
    Utils::pause();
}

void InventorySystem::viewProducts() const {
    Utils::clearScreen();
    Utils::printBanner("View All Products");
    table.displayAll();
    Utils::pause();
}

void InventorySystem::searchProduct() const {
    Utils::clearScreen();
    Utils::printBanner("Search Product (Hash Lookup)");

    int id = 0;
    Validator::readInt("Enter Product ID: ", id, 1, 2000000000);

    const Product* found = table.search(id);
    if (found == nullptr) {
        std::cout << "Product not found.\n";
    } else {
        std::cout << "\nProduct found via hash table:\n";
        found->display();
    }
    Utils::pause();
}

void InventorySystem::updateProduct() {
    Utils::clearScreen();
    Utils::printBanner("Update Product");

    int id = 0;
    Validator::readInt("Enter Product ID to update: ", id, 1, 2000000000);

    Product* existing = table.search(id);
    if (existing == nullptr) {
        std::cout << "Product not found.\n";
        Utils::pause();
        return;
    }

    std::cout << "\nCurrent details:\n";
    existing->display();
    std::cout << "Enter new details (Product ID cannot change):\n";

    std::string name;
    std::string category;
    std::string supplier;
    int qty = 0;
    double purchase = 0.0;
    double selling = 0.0;

    Validator::readNonEmptyString("Product Name: ", name, Product::NAME_LEN - 1);
    Validator::readNonEmptyString("Category: ", category, Product::CATEGORY_LEN - 1);
    Validator::readInt("Quantity: ", qty, 0, 1000000000);
    Validator::readDouble("Purchase Price: ", purchase, 0.0);
    Validator::readDouble("Selling Price: ", selling, 0.0);
    Validator::readNonEmptyString("Supplier Name: ", supplier, Product::SUPPLIER_LEN - 1);

    Product updated(id, name, category, qty, purchase, selling, supplier);
    if (table.update(updated)) {
        dirty = true;
        saveData();
        std::cout << "Product updated successfully.\n";
    } else {
        std::cout << "Error: Update failed.\n";
    }
    Utils::pause();
}

void InventorySystem::deleteProduct() {
    Utils::clearScreen();
    Utils::printBanner("Delete Product");

    int id = 0;
    Validator::readInt("Enter Product ID to delete: ", id, 1, 2000000000);

    const Product* existing = table.search(id);
    if (existing == nullptr) {
        std::cout << "Product not found.\n";
        Utils::pause();
        return;
    }

    std::cout << "\nAbout to delete:\n";
    existing->display();
    std::cout << "Confirm delete? (1 = Yes, 0 = No): ";
    int confirm = 0;
    if (!(std::cin >> confirm)) {
        Validator::clearInput();
        std::cout << "Cancelled.\n";
        Utils::pause();
        return;
    }
    Validator::clearInput();

    if (confirm != 1) {
        std::cout << "Delete cancelled.\n";
        Utils::pause();
        return;
    }

    if (table.remove(id)) {
        dirty = true;
        saveData();
        std::cout << "Product deleted successfully.\n";
    } else {
        std::cout << "Error: Delete failed.\n";
    }
    Utils::pause();
}

void InventorySystem::manageStock() {
    Utils::clearScreen();
    Utils::printBanner("Stock Management");
    std::cout << "  1. Add Stock\n"
              << "  2. Reduce Stock\n"
              << "  0. Back\n";

    int choice = 0;
    Validator::readInt("Choice: ", choice, 0, 2);
    if (choice == 0) {
        return;
    }

    int id = 0;
    Validator::readInt("Product ID: ", id, 1, 2000000000);
    Product* product = table.search(id);
    if (product == nullptr) {
        std::cout << "Product not found.\n";
        Utils::pause();
        return;
    }

    std::cout << "Current quantity: " << product->quantity << '\n';
    int amount = 0;
    Validator::readInt("Amount: ", amount, 1, 1000000000);

    if (choice == 1) {
        product->quantity += amount;
        dirty = true;
        saveData();
        std::cout << "Stock increased. New quantity: " << product->quantity << '\n';
    } else {
        if (amount > product->quantity) {
            std::cout << "Error: Insufficient stock. Available: " << product->quantity << '\n';
        } else {
            product->quantity -= amount;
            dirty = true;
            saveData();
            std::cout << "Stock reduced. New quantity: " << product->quantity << '\n';
        }
    }
    Utils::pause();
}

void InventorySystem::generateReports() const {
    Utils::clearScreen();
    Utils::printBanner("Inventory Reports");

    if (table.isEmpty()) {
        std::cout << "No products to report.\n";
        Utils::pause();
        return;
    }

    int lowStockThreshold = 5;
    Validator::readInt("Low-stock threshold (default suggestion 5): ",
                       lowStockThreshold, 0, 1000000000);

    int totalQty = 0;
    double purchaseValue = 0.0;
    double sellingValue = 0.0;
    int lowStockCount = 0;

    std::cout << "\n--- Low Stock Items (qty <= " << lowStockThreshold << ") ---\n";
    Utils::printHeaderRow();
    Utils::printLine('-', 94);

    table.forEach([&](const Product& p) {
        totalQty += p.quantity;
        purchaseValue += p.quantity * p.purchasePrice;
        sellingValue += p.quantity * p.sellingPrice;
        if (p.quantity <= lowStockThreshold) {
            ++lowStockCount;
            p.displayRow();
        }
    });

    if (lowStockCount == 0) {
        std::cout << "(none)\n";
    }
    Utils::printLine('-', 94);

    std::cout << std::fixed << std::setprecision(2)
              << "\n--- Summary ---\n"
              << " Total products      : " << table.size() << '\n'
              << " Total units in stock: " << totalQty << '\n'
              << " Low-stock items     : " << lowStockCount << '\n'
              << " Inventory cost value: " << purchaseValue << '\n'
              << " Inventory sell value: " << sellingValue << '\n'
              << " Potential profit    : " << (sellingValue - purchaseValue) << '\n';

    Utils::pause();
}

void InventorySystem::run() {
    loadData();

    bool running = true;
    while (running) {
        showMainMenu();
        int choice = 0;
        Validator::readInt("Select option: ", choice, 1, 9);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewProducts();
                break;
            case 3:
                searchProduct();
                break;
            case 4:
                updateProduct();
                break;
            case 5:
                deleteProduct();
                break;
            case 6:
                manageStock();
                break;
            case 7:
                generateReports();
                break;
            case 8:
                saveData();
                Utils::pause();
                break;
            case 9:
                if (dirty) {
                    saveData();
                }
                Utils::clearScreen();
                Utils::printBanner("Thank you for using Inventory Control System");
                std::cout << "Goodbye!\n";
                running = false;
                break;
            default:
                break;
        }
    }
}
