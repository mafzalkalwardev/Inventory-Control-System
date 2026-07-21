#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "Product.h"
#include <functional>
#include <vector>

class HashTable {
public:
    static const int TABLE_SIZE = 101;

    HashTable();
    ~HashTable();

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    bool insert(const Product& product);
    Product* search(int productId);
    const Product* search(int productId) const;
    bool remove(int productId);
    bool update(const Product& product);
    void clear();
    bool isEmpty() const;
    int size() const;
    void displayAll() const;

    // Visit every product (used by FileHandler and reports)
    void forEach(const std::function<void(const Product&)>& visit) const;
    void forEachMutable(const std::function<void(Product&)>& visit);

    std::vector<Product> getAllProducts() const;

private:
    struct Node {
        Product data;
        Node* next;
        explicit Node(const Product& product);
    };

    Node* table[TABLE_SIZE];
    int count;

    int hashFunction(int productId) const;
};

#endif
