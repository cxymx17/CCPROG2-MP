## SHOPPING APP in C

### Summary:
A console-based shopping system in C that allows users to register, buy, and sell items. The app manages user accounts, products, carts, and transactions with features for both buyers and sellers, including admin-level sales analytics and report generation.

#### Detailed:
This project is a feature-rich, menu-driven shopping application built in C, designed to simulate a small-scale online marketplace. It supports registration and login for up to 100 users, who can act as buyers, sellers, or both. Each user has a profile with a unique ID, password, name, address, and contact number. Sellers can list up to 20 different items, each with attributes like product ID, name, category, description, available quantity, price, and seller ID.

Sellers have access to a dedicated menu where they can add new products, edit existing inventory (change price, restock, update descriptions, etc.), and view their stock in tabular format, including highlighting items low in stock. Buyers can browse all available products by seller, search by category or name, and manage a personal cart with up to 10 items at a time. Buyers can add, update, or remove items from their cart and proceed to checkout, which generates transactions, each limited to five items from a single seller per transaction, with clear receipts and automatic inventory updates.

All transactions are recorded, including date, buyer and seller IDs, and transaction totals. If a buyer exits with items still in the cart, the cart is saved for future sessions. The application includes an admin menu with password protection, allowing the administrator to view all users and sellers, monitor total sales, and generate reports (like sales within a date range, sales per seller, and top buyers or "shopaholics").

Persistent storage is implemented through text files for users and items, and text or binary files for transactions and saved carts. The program features robust error handling (e.g., unique IDs, inventory limits, cart constraints, preventing buyers from purchasing their items), clear navigation, and a modular code structure using arrays, structures, and user-defined functions. Internal documentation and coding conventions are followed as required for academic submissions.

This project offers a comprehensive practice in file handling, data structures, modular programming, and user interaction in C, and may be extended with additional features like sales statistics or product recommendations.
