#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include "Product.h"

class Store { 

public:
    std::vector<Product> products;
    float storeValue;

public:
    Store() = default;

    void addProduct(const Product& product);
    bool updateProduct(const std::string& code, const Product& product);
    bool deleteProduct(const std::string& code);
    void deleteExpiredProducts();
    void writeProductToFile(const Product& product);
    void writeAllProductsToFile(std::vector<Product> products);

    std::vector<Product> getAllProducts();
    std::vector<Product> getValidProducts();
    std::vector<Product> getExpiredProducts();
    float calculateInventoyCost();
};
