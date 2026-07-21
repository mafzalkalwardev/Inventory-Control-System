# Project Report

## Inventory Control System Using Hashing and Database Management System

### Course

Data Structures (C++)

---

## 1. Introduction

This project implements a computerized inventory control system in C++. Small businesses often track stock manually, which leads to slow searches, duplicate records, and inaccurate quantities. The system addresses these issues by combining a **hash table** for fast in-memory operations with **binary file handling** for permanent storage.

## 2. Problem Statement

Manual inventory management is error-prone and inefficient. Searching for a product in a large list is typically linear time. This project provides a menu-driven application where Product ID lookup uses hashing with average time complexity **O(1)**, while all records remain available after the program exits.

## 3. Objectives

- Develop an inventory management system in C++.
- Implement hashing for fast product searching.
- Store product records permanently using file handling.
- Provide a user-friendly menu-driven interface.
- Manage product stock efficiently and produce basic inventory reports.

## 4. Scope

Users can:

- Add new products
- View all products
- Search products by Product ID
- Update product details
- Delete products
- Manage stock quantity (add / reduce)
- Display inventory reports
- Authenticate via a simple login screen

## 5. Tools and Technologies

| Item | Choice |
|------|--------|
| Language | C++17 |
| Data structure | Hash table with separate chaining |
| Database | Binary file (`inventory.dat`) |
| Build | CMake |
| Platform | Windows (primary) |

## 6. System Architecture

### 6.1 Frontend (console UI)

- Login screen
- Main menu
- Add / View / Search / Update / Delete Product
- Stock management
- Inventory reports
- Exit (with save)

### 6.2 Backend

- `HashTable` — insert, search, remove, update, display
- Hash function — `productId % TABLE_SIZE`
- Collision handling — separate chaining
- `FileHandler` — load/save binary inventory; user authentication file
- Input validation
- Report generation

## 7. Product Information

Each product record contains:

- Product ID (integer key)
- Product Name
- Category
- Quantity
- Purchase Price
- Selling Price
- Supplier Name

Fixed-size character arrays are used so records can be written and read safely in binary form.

## 8. Data Structure Design

### 8.1 Hash Table

- Table size: **101** (prime, reduces clustering of keys)
- Each bucket holds a singly linked list of nodes
- Key: Product ID

### 8.2 Hash Function

```
h(key) = key % 101
```

Negative IDs are normalized so the index stays in range `[0, 100]`.

### 8.3 Collision Handling — Separate Chaining

When two Product IDs hash to the same index, both records are stored in the linked list at that bucket. Insertion adds at the head of the list. Search walks the chain until the matching ID is found or the list ends.

**Advantages for this project:**

- Deletion is straightforward (unlink the node)
- Table never “fills up” like open addressing
- Easy to explain in a Data Structures course

### 8.4 Time Complexity

| Operation | Average | Worst case |
|-----------|---------|------------|
| Insert | O(1) | O(n) |
| Search | O(1) | O(n) |
| Delete | O(1) | O(n) |

Worst case occurs if every key collides into one chain.

## 9. File Handling (Database Layer)

At startup, the program loads `data/inventory.dat` into the hash table (if the file exists). After each successful write operation (add, update, delete, stock change), the table is written back to disk:

1. Write a 32-bit integer count
2. Write `count` consecutive `Product` records

Login credentials are stored in `data/users.dat` as plaintext username/password pairs (acceptable for coursework; not suitable for production).

## 10. Functional Modules

| Module | Responsibility |
|--------|----------------|
| `Product` | Record layout and display |
| `HashTable` | Core hashing ADT |
| `FileHandler` | Persistence and authentication |
| `Validator` | Safe numeric/string input |
| `Utils` | Screen clear, banners, pause |
| `InventorySystem` | Menus and business rules |
| `main` | Entry point, path setup, login → run |

## 11. Non-Functional Aspects

- **Fast searching** via hashing
- **Usable** numbered menus and validation messages
- **Reliable** save-after-write persistence
- **Accurate** stock checks before reducing quantity
- **Simple security** via login (not cryptographically secure)

## 12. Testing Outline

1. Login with `admin` / `admin123`
2. Add several products (see `sample/seed_products.txt`)
3. Search by Product ID — confirm hash lookup finds the record
4. Update a product and verify changes in View All
5. Reduce stock beyond quantity — expect an error
6. Generate reports and confirm low-stock listing
7. Exit and restart — confirm data still present

## 13. Future Enhancements

- Barcode scanner integration
- Supplier management module
- Customer billing and sales reports
- Stronger password hashing
- Graphical user interface (GUI)
- SQL database integration

## 14. Conclusion

The Inventory Control System demonstrates a practical use of hashing in C++. By pairing a hash table with binary file persistence, the project meets course goals for data structures while solving a realistic inventory problem: fast Product ID search, durable records, and clear stock control.

---

*End of report*
