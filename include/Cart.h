#pragma once
#include "Product.h"
#include <vector>
#include <map>

class Cart {
    std::map<std::string, Product> products;

    public:
        Cart() {}  // Default constructor - Cart is initially empty
        void addProduct(const Product &product);
        bool isProductInCart(const std::string &title);
        void setProductAmount(const std::string &title, float amount);
        float getProductAmount(const std::string &title);
        std::map<std::string, Product> getProducts() const { return products; };
        void removeProduct(const std::string &title);
        bool isEmpty() { return products.size() == 0; }
        std::string getFirstProductTitle() const { return products.begin()->first; }
        void empty() { products.clear(); }
        void show();
};