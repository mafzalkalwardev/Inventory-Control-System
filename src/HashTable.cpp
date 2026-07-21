#include "HashTable.h"
#include "Utils.h"
#include <iostream>

HashTable::Node::Node(const Product& product) : data(product), next(nullptr) {}

HashTable::HashTable() : count(0) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    clear();
}

int HashTable::hashFunction(int productId) const {
    int index = productId % TABLE_SIZE;
    if (index < 0) {
        index += TABLE_SIZE;
    }
    return index;
}

bool HashTable::insert(const Product& product) {
    if (search(product.productId) != nullptr) {
        return false;
    }

    const int index = hashFunction(product.productId);
    Node* node = new Node(product);
    node->next = table[index];
    table[index] = node;
    ++count;
    return true;
}

Product* HashTable::search(int productId) {
    Node* current = table[hashFunction(productId)];
    while (current != nullptr) {
        if (current->data.productId == productId) {
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;
}

const Product* HashTable::search(int productId) const {
    Node* current = table[hashFunction(productId)];
    while (current != nullptr) {
        if (current->data.productId == productId) {
            return &current->data;
        }
        current = current->next;
    }
    return nullptr;
}

bool HashTable::remove(int productId) {
    const int index = hashFunction(productId);
    Node* current = table[index];
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data.productId == productId) {
            if (previous == nullptr) {
                table[index] = current->next;
            } else {
                previous->next = current->next;
            }
            delete current;
            --count;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

bool HashTable::update(const Product& product) {
    Product* existing = search(product.productId);
    if (existing == nullptr) {
        return false;
    }
    *existing = product;
    return true;
}

void HashTable::clear() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        table[i] = nullptr;
    }
    count = 0;
}

bool HashTable::isEmpty() const {
    return count == 0;
}

int HashTable::size() const {
    return count;
}

void HashTable::displayAll() const {
    if (isEmpty()) {
        std::cout << "\nNo products in inventory.\n";
        return;
    }

    Utils::printHeaderRow();
    Utils::printLine('-', 94);
    forEach([](const Product& product) { product.displayRow(); });
    Utils::printLine('-', 94);
    std::cout << "Total products: " << count << '\n';
}

void HashTable::forEach(const std::function<void(const Product&)>& visit) const {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            visit(current->data);
            current = current->next;
        }
    }
}

void HashTable::forEachMutable(const std::function<void(Product&)>& visit) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            visit(current->data);
            current = current->next;
        }
    }
}

std::vector<Product> HashTable::getAllProducts() const {
    std::vector<Product> products;
    products.reserve(static_cast<std::size_t>(count));
    forEach([&products](const Product& product) { products.push_back(product); });
    return products;
}
