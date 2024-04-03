// StoreManagement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
#include "Product.h"
#include "Store.h"

Product searchProductByName(const std::string& currentName) {
    Store store;
    store.products = store.getAllProducts();
    Product p;
    for (int i = 0; i < store.products.size(); i++)
    {
        if (store.products[i].getName() == currentName) {
            p = store.products[i];
            break;
        }
    }
    return p;
}
void printProductsContainingString(const std::string& currentString)
{
    Store store;
    store.products = store.getAllProducts();
    Product p;
    bool found = false;
    for (int i = 0; i < store.products.size(); i++)
    {
        if (store.products[i].getName().find(currentString) != std::string::npos) {
            std::cout << store.products[i] << std::endl;
            found = true;
        }
    }
    if (!found)
        std::cout << "Product containing string <" << currentString << "> doesn't exist in store!\n";
}

Product searchProductByCode(const std::string& currentCode) {
    Store store;
    store.products = store.getAllProducts();
    Product p;
    for (int i = 0; i < store.products.size(); i++)
    {
        if (store.products[i].getCode() == currentCode) {
            p = store.products[i];
            break;
        }
    }
    return p;
}

void printHeader()
{
    std::cout << "Product Code         Product Name        Price      Quantity       Production Date      Expiration Date\n";
    std::cout << "-------------------------------------------------------------------------------------------------------\n";
    std::cout << std::fixed << std::setprecision(2);
}

void printStore()
{
    Store store;
    store.products = store.getAllProducts();
    printHeader();
    for (int i = 0; i < store.products.size(); i++)
    {
        std::cout << store.products[i] << std::endl;
    }
}

void printAvailableProducts()
{
    Store store;
    store.products = store.getAllProducts();
    printHeader();
    for (int i = 0; i < store.products.size(); i++)
    {
        if (store.products[i].getQuantity() > 0)
            std::cout << store.products[i] << std::endl;
    }
}

void printExpiredProducts()
{
    Store store;
    std::vector<Product> prodList = store.getExpiredProducts();
    printHeader();
    for (int i = 0; i < prodList.size(); i++)
    {
        std::cout << prodList[i] << std::endl;
    }
}

void addProduct()
{
    Store store;
    std::string code;
    std::string name;
    float price;
    int quantity;
    std::string productDate;
    std::string expirationDate;
    std::cout << "Code: ";
    std::cin >> code;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "Price: ";
    std::cin >> price;
    std::cout << "Quantity: ";
    std::cin >> quantity;
    std::cout << "Production Date: ";
    std::cin >> productDate;
    std::cout << "Expiration Date: ";
    std::cin >> expirationDate;
    store.addProduct(Product(code, name, price, quantity, productDate, expirationDate));
    std::cout << "A new product with code <" << code << "> was successfully added!\n";
}

bool updateProduct(const std::string& code, Product& product)
{
    Store store;
    std::string newCode;
    std::string name;
    float price;
    int quantity;
    std::string productDate;
    std::string expirationDate;
    int choice;
    std::cout << "Please choose the field to update!\n\n";
    std::cout << "1. Code\n";
    std::cout << "2. Name\n";
    std::cout << "3. Price\n";
    std::cout << "4. Quantity\n";
    std::cout << "5. Production date\n";
    std::cout << "6. Expiration date\n";
    std::cin >> choice;

    switch (choice) {
    case 1: 
        std::cout << "Code: ";
        std::cin >> newCode;
        product.setCode(newCode);
        break;
    case 2:
        std::cout << "Name: ";
        std::cin >> name;
        product.setName(name);
        break;
    case 3:
        std::cout << "Price: ";
        std::cin >> price;
        product.setPrice(price);
        break;
    case 4:
        std::cout << "Quantity: ";
        std::cin >> quantity;
        product.setQuantity(quantity);
        break;
    case 5:
        std::cout << "Production Date: ";
        std::cin >> productDate;
        product.setProductioDate(productDate);
        break;
    case 6:
        std::cout << "Expiration Date: ";
        std::cin >> expirationDate;
        product.setExpirationDate(expirationDate);
        break;
    default: std::cout << "Invalid choice!\n";
        break;
    }
    
    if (product.getCode() != "") {
        return store.updateProduct(code, product);
    }
    return false;
}

int main()
{

    int choice;
    std::string code;
    std::string name;

    std::cout << "Please choose an option!\n\n";

    do {

        std::cout << "1. Add a new product\n";
        std::cout << "2. Update a product\n";
        std::cout << "3. Delete a product by code\n";
        std::cout << "4. Delete all expired products\n";
        std::cout << "5. Search a product by code\n";
        std::cout << "6. Search a product by name\n";
        std::cout << "7. Search a product which contains a string\n";
        std::cout << "8. Print all products \n";
        std::cout << "9. Print all products in stock\n";
        std::cout << "10. Print all expired products\n";
        std::cout << "11. Print total inventory cost\n";
        std::cout << "12. Exit\n\n";

        std::cin >> choice;
        Store store;
        Product productToFind;
        switch (choice) {
        case 1: 
            std::cout << "Product to add: \n";
            addProduct();
            break;
        case 2: std::cout << "Product code to update: ";
            std::cin >> code;
            productToFind = searchProductByCode(code);
            if (productToFind.getCode()._Equal("")) {
                std::cout << "Product with code <" << code << "> doesn't exist in store!\n";
                break;
            }
            if (updateProduct(code, productToFind))
                std::cout << "Product with code <" << code << "> successfully updated!\n";            
            else 
                std::cout << "Product with code <" << code << "> doesn't exist in store!\n";            
            break;
        case 3: std::cout << "Product code to delete: ";
            std::cin >> code;
            if (store.deleteProduct(code))
                std::cout << "Product with code <" << code << "> successfully deleted!\n";
            else
                std::cout << "Product with code <" << code << "> doesn't exist in store!\n";
            break;
        case 4: store.deleteExpiredProducts();
            std::cout << "All expired products were deleted!\n";
            break;
        case 5: std::cout << "Search a product by code: ";
            std::cin >> code;
            productToFind = searchProductByCode(code);
            if (productToFind.getCode() != "") {
                std::cout << productToFind << std::endl;
            }
            else {
                std::cout << "Product with code <" << code << "> doesn't exist in store!\n";
            }
            break;
        case 6: std::cout << "Search a product by name: ";
            std::cin >> name;
            productToFind = searchProductByName(name);
            if (productToFind.getName() != "") {
                std::cout << productToFind << std::endl;
            }
            else {
                std::cout << "Product with name <" << name << "> doesn't exist in store!\n";
            }
            break;
        case 7: std::cout << "Search a product which contains the string: ";
            std::cin >> name;
            printProductsContainingString(name);
            break;
        case 8: std::cout << "Store content is:\n";
            printStore();
            std::cout << "\n";
            break;
        case 9: std::cout << "All products available are:\n";
            printAvailableProducts();
            std::cout << "\n";
            break;
        case 10: std::cout << "All expired products are:\n"; 
            printExpiredProducts();
            std::cout << "\n";
            break;
        case 11: std::cout << "Total inventory cost is:\n";
            std::cout << store.calculateInventoyCost() << "\n";
            break;
        case 12: std::cout << "Exit!";
            break;
        default: std::cout << "Invalid choice!\n";
            break;
        }
        if (choice != 12)
            std::cout << "\nPlease choose a new option!\n";
    } while (choice != 12);

    return 0;

}
