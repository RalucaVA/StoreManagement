#pragma warning(disable:4996)
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "Product.h"
#include "Store.h"

std::vector<Product> readCSV(const std::string& filename) {
    std::vector<Product> products;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return products;
    }

    std::string line;
    Product p;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string code, name, priceString, quantityString, prodDate, expirationDate;

        if (std::getline(iss, code, ',') &&
            std::getline(iss, name, ',') &&
            std::getline(iss, priceString, ',') &&
            std::getline(iss, quantityString, ',') &&
            std::getline(iss, prodDate, ',') &&
            std::getline(iss, expirationDate, ',')) {
            int quantity = std::stoi(quantityString);
            float price = std::stof(priceString);
            Product p = Product(code, name, price, quantity, prodDate, expirationDate);
            products.push_back(p);
        }
    }

    file.close();

    return products;
}

void Store::writeProductToFile(const Product& product) {
    std::ofstream file;
    file.open("store.csv", std::ofstream::app);
    file << product.getCode() << "," << product.getName() << ", " << product.getPrice() << ", " << product.getQuantity() << "," << product.getProductionDate() << "," << product.getExpirationDate() << "\n";
    file.close();
}

void Store::writeAllProductsToFile(std::vector<Product> products) {
    std::ofstream file;
    file.open("tmp.csv", std::ofstream::app);
    for (const auto& product : products) {
        file << product.getCode() << "," << product.getName() << ", " << product.getPrice() << ", " << product.getQuantity() << "," << product.getProductionDate() << "," << product.getExpirationDate() << "\n";
    }
    file.close();
    std::remove("store.csv");
    std::rename("tmp.csv", "store.csv");
}

bool isDateBeforeCurrent(const std::string& dateString) {
    const std::string format = "%Y-%m-%d";
    std::tm date = {};
    std::istringstream iss(dateString);
    iss >> std::get_time(&date, format.c_str());

    if (iss.fail()) {
        // Handle invalid date format. i.e if you want to convert the word "Hello" to date type
        std::cout << "Invalid date format: " + dateString;
        return false;
    }

    std::time_t currentTime = std::time(nullptr);
    std::tm* currentDate = std::localtime(&currentTime);

    if (date.tm_year < currentDate->tm_year) {
        return true;
    }
    else if (date.tm_year == currentDate->tm_year) {
        if (date.tm_mon < currentDate->tm_mon) {
            return true;
        }
        else if (date.tm_mon == currentDate->tm_mon) {
            if (date.tm_mday < currentDate->tm_mday) {
                return true;
            }
        }
    }

    return false;
}

void Store::addProduct(const Product& product) {
    writeProductToFile(product);
}

bool Store::updateProduct(const std::string& code, const Product& product) {
    products = getAllProducts();
    auto it = std::find_if(products.begin(), products.end(),
        [&code](const Product& p) { return p.getCode() == code; });
    if (it != products.end()) {
        products.erase(it);
        products.push_back(product);
        writeAllProductsToFile(products);
        return true;
    }
    return false;
}

bool Store::deleteProduct(const std::string& code) {
    products = getAllProducts();
    auto it = std::find_if(products.begin(), products.end(),
        [&code](const Product& p) { return p.getCode() == code; });

    if (it != products.end()) {
        products.erase(it);
        writeAllProductsToFile(products);
        return true;        
    }
    return false;
}

void Store::deleteExpiredProducts() {
    std::vector<Product> validProductList = getValidProducts();
    writeAllProductsToFile(validProductList);
}

std::vector<Product> Store::getAllProducts()
{
    return readCSV("store.csv");
}

std::vector<Product> Store::getValidProducts() 
{
    products = getAllProducts();
    std::vector<Product> validProducts;
    for (const auto& product : products) {
        if (!isDateBeforeCurrent(product.getExpirationDate())) {
            validProducts.push_back(product);
        }
    }
    return validProducts;
}

std::vector<Product> Store::getExpiredProducts()
{
    products = getAllProducts();
    std::vector<Product> expiredProducts;
    for (const auto& product : products) {
        if (isDateBeforeCurrent(product.getExpirationDate())) {
            expiredProducts.push_back(product);
        }
    }
    return expiredProducts;
}

float Store::calculateInventoyCost()
{
    Store store;
    store.products = store.getAllProducts();
    float inventory = 0.0;
    for (int i = 0; i < store.products.size(); i++)
    {
        inventory += store.products[i].getProductInventoryCost();
    }
    return inventory;
}


