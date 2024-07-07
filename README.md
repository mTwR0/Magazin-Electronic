
# Electronic Store Management System

## Project Description
This C++ project demonstrates the usage of classes, constructors, getters, setters, and operator overloading through a simulation of an electronic store management system.

The system supports two types of accounts: store accounts and client accounts. The initial store account has the username "admin" and password "admin". The store account allows users to add products to inventory, which are then accessible by client accounts. Client accounts can manage a shopping cart and place orders.

## Features
- **Store Account:**
  - Add, edit, and delete products in inventory.
  - Save inventory to text and binary files.
- **Client Account:**
  - Add, remove, and display products in the shopping cart.
  - Place orders.
- **General:**
  - Demonstrates object-oriented programming principles.
  - Utilizes txt files for storage of inventory data.


## Usage
Upon running the program, you will be presented with two options:
1. Test the functionality of getters, setters, constructors, and operators.
2. Enter the electronic store system.

In the electronic store system, you can create and manage client accounts, log into the store account (initially using "admin" for both username and password), and perform various operations related to product inventory and shopping cart management.

## Class Details
Below are details about a few of the more important classes used in the project.
### AfisareMeniu
This class serves as a base for displaying menus

### Magazin
Contains details about the store, including:
- **Attributes:**
  - `numeMagazin`: Name of the store.
  - `locatieMagazin`: Location of the store.
  - `nrMagazine`: Number of stores in a city.
- **Methods:**
  - Constructors, destructor, getters, setters, and overloaded operators (`=`, `<<`, `>>`).

### Produs
Handles adding, editing, deleting, and displaying products in the store inventory.
- **Attributes:**
  - `numeProdus`: Name of the product.
  - `cantitateProdus`: Quantity of the product.
  - `pretProdus`: Price of the product.
  - `produse` and `inventar`: Vectors for storing products.
- **Methods:**
  - Constructors, destructor, getters, setters, and overloaded operators (`=`, `<<`, `>>`).
  - Methods for displaying, adding, editing, deleting products, and saving products to text and binary files.

### Client
Manages client accounts and their interactions with the shopping cart.
- **Attributes:**
  - `username`: Username of the client.
  - `password`: Password of the client.
- **Methods:**
  - Constructors, destructor, getters, setters, and overloaded operators (`=`, `<<`, `>>`).
  - Methods for adding, removing, and displaying products in the cart, and placing orders.

### Utilizator
Handles the creation and management of user accounts.
- **Attributes:**
  - `username`: Username of the user.
  - `password`: Password of the user.
- **Methods:**
  - Constructors, destructor, getters, setters, and overloaded operators (`=`, `<<`, `>>`).
  - Methods for creating and validating user accounts.

## Acknowledgements
Special thanks to my friends in college ( Vik , Anca , Alex )  who contributed to the development of this project.
