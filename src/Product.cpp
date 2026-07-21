#include "Product.h"
#include <cstring>
#include <iomanip>

namespace {
void copyFixed(char* dest, std::size_t destSize, const std::string& src) {
    std::memset(dest, 0, destSize);
    if (src.empty()) {
        return;
    }
    const std::size_t copyLen = (src.size() < destSize - 1) ? src.size() : destSize - 1;
    std::memcpy(dest, src.c_str(), copyLen);
    dest[copyLen] = '\0';
}
}  // namespace

Product::Product()
    : productId(0), quantity(0), purchasePrice(0.0), sellingPrice(0.0) {
    std::memset(name, 0, NAME_LEN);
    std::memset(category, 0, CATEGORY_LEN);
    std::memset(supplier, 0, SUPPLIER_LEN);
}

Product::Product(int id,
                 const std::string& productName,
                 const std::string& productCategory,
                 int qty,
                 double purchase,
                 double selling,
                 const std::string& supplierName)
    : productId(id), quantity(qty), purchasePrice(purchase), sellingPrice(selling) {
    setName(productName);
    setCategory(productCategory);
    setSupplier(supplierName);
}

void Product::setName(const std::string& productName) {
    copyFixed(name, NAME_LEN, productName);
}

void Product::setCategory(const std::string& productCategory) {
    copyFixed(category, CATEGORY_LEN, productCategory);
}

void Product::setSupplier(const std::string& supplierName) {
    copyFixed(supplier, SUPPLIER_LEN, supplierName);
}

void Product::display() const {
    std::cout << "----------------------------------------\n"
              << " Product ID      : " << productId << '\n'
              << " Name            : " << name << '\n'
              << " Category        : " << category << '\n'
              << " Quantity        : " << quantity << '\n'
              << " Purchase Price  : " << std::fixed << std::setprecision(2) << purchasePrice << '\n'
              << " Selling Price   : " << sellingPrice << '\n'
              << " Supplier        : " << supplier << '\n'
              << "----------------------------------------\n";
}

void Product::displayRow() const {
    std::cout << std::left
              << std::setw(8) << productId
              << std::setw(22) << name
              << std::setw(14) << category
              << std::setw(8) << quantity
              << std::setw(12) << std::fixed << std::setprecision(2) << purchasePrice
              << std::setw(12) << sellingPrice
              << std::setw(18) << supplier
              << '\n';
}
