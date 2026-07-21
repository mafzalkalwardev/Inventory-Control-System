#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include "FileHandler.h"
#include "HashTable.h"
#include <string>

class InventorySystem {
public:
    InventorySystem(const std::string& inventoryPath, const std::string& usersPath);

    bool login();
    void run();

private:
    HashTable table;
    std::string inventoryPath;
    std::string usersPath;
    bool dirty;

    void loadData();
    void saveData();

    void showMainMenu() const;
    void addProduct();
    void viewProducts() const;
    void searchProduct() const;
    void updateProduct();
    void deleteProduct();
    void manageStock();
    void generateReports() const;
};

#endif
