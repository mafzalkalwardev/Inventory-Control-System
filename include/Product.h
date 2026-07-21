#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

struct Product {
    static const int ID_LEN = 16;
    static const int NAME_LEN = 64;
    static const int CATEGORY_LEN = 32;
    static const int SUPPLIER_LEN = 64;

    int productId;
    char name[NAME_LEN];
    char category[CATEGORY_LEN];
    int quantity;
    double purchasePrice;
    double sellingPrice;
    char supplier[SUPPLIER_LEN];

    Product();
    Product(int id,
            const std::string& productName,
            const std::string& productCategory,
            int qty,
            double purchase,
            double selling,
            const std::string& supplierName);

    void setName(const std::string& productName);
    void setCategory(const std::string& productCategory);
    void setSupplier(const std::string& supplierName);

    void display() const;
    void displayRow() const;
};

#endif
