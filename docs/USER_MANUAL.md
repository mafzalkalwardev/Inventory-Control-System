# User Manual

## Inventory Control System

### 1. Starting the Application

1. Build the project (see [README.md](../README.md)).
2. Run `InventoryControl.exe` from the `build` folder (or your IDE run configuration).
3. Ensure a `data` folder is available next to the working directory (created automatically if missing). The build step also copies `users.dat`.

### 2. Login

At the login screen enter:

- **Username:** `admin`
- **Password:** `admin123`

You have three attempts. After a successful login, the inventory file is loaded into the hash table.

### 3. Main Menu

| Option | Action |
|--------|--------|
| 1 | Add Product |
| 2 | View All Products |
| 3 | Search Product (by Product ID) |
| 4 | Update Product |
| 5 | Delete Product |
| 6 | Stock Management |
| 7 | Inventory Reports |
| 8 | Save Inventory (manual save) |
| 9 | Exit |

The menu shows how many products are in memory and whether there are unsaved changes. Most write operations also auto-save.

### 4. Add Product

Enter:

1. Product ID (must be unique and positive)
2. Name, Category
3. Quantity (≥ 0)
4. Purchase price and selling price (≥ 0)
5. Supplier name

Duplicate IDs are rejected.

### 5. View All Products

Displays a table of every product currently in the hash table.

### 6. Search Product

Enter a Product ID. The system computes `ID % 101`, then searches the chain at that bucket. If found, full product details are shown.

### 7. Update Product

Enter the Product ID, review current details, then enter the new field values. The Product ID itself cannot change.

### 8. Delete Product

Enter the Product ID, confirm with `1` (Yes) or `0` (No).

### 9. Stock Management

1. Choose **Add Stock** or **Reduce Stock**
2. Enter Product ID and amount
3. Reduce Stock fails if the amount exceeds the current quantity

### 10. Inventory Reports

1. Enter a low-stock threshold (for example `5`)
2. The report lists items at or below that quantity
3. Summary includes total products, total units, inventory cost value, sell value, and potential profit

### 11. Sample Data

See [sample/seed_products.txt](../sample/seed_products.txt) for example products you can enter manually for a demo or viva.

### 12. Troubleshooting

| Issue | What to try |
|-------|-------------|
| Login always fails | Confirm `data/users.dat` exists and contains `admin admin123` |
| Data missing after restart | Run the executable from the `build` directory so `data/inventory.dat` is found |
| Build fails | Install MinGW-w64 and CMake; use the generators in the README |
| Invalid input loops | Enter numbers where prompted; empty names are not allowed |

### 13. Exiting

Choose option **9**. If there are unsaved changes, the system saves before exit.
