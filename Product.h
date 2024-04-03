#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

class Product {
private:
    std::string code;
    std::string name;
    float price;
    int quantity;
    std::string productionDate;
    std::string expirationDate;

public:
    Product() = default;

    Product(const std::string& code, const std::string& name, float price, int quantity,
        const std::string& productionDate, const std::string& expirationDate)
        : code(code), name(name), price(price), quantity(quantity),
        productionDate(productionDate), expirationDate(expirationDate) {}

#pragma region Getters
    std::string getCode() const { return code; }
    std::string getName() const { return name; }
    float getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    std::string getProductionDate() const { return productionDate; }
    std::string getExpirationDate() const { return expirationDate; }
#pragma endregion

#pragma region Setters
    void setCode(const std::string& newCode) { code = newCode; }
    void setName(const std::string& newName) { name = newName; }
    void setPrice(const float newPrice) { price = newPrice; }
    void setQuantity(const int newQuantity) { price = newQuantity; }
    void setProductioDate(const std::string& newDate) { productionDate = newDate; }
    void setExpirationDate(const std::string& newDate) { expirationDate = newDate; }
#pragma endregion


    float getProductInventoryCost() {
        return getPrice() * getQuantity();
    }

    // Overloaded print operators
    friend std::ostream& operator<<(std::ostream& os, const Product& product) {
        std::cout << product.getCode() + "     " +
            product.getName() + "      " <<
            product.getPrice() << "       " +
            std::to_string(product.getQuantity()) + "             " +
            product.getProductionDate() + "              " +
            product.getExpirationDate() ;
        return os;
    }

};
