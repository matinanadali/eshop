#pragma once
#include "Product.h"
#include <vector>
#include <iostream>
#include <fstream>

class Order {
    std::vector<Product> products;
    float totalCost;

    public:
    Order() {};
    Order(const std::vector<Product> &products, float totalCost): products(products), totalCost(totalCost) {};
    void showOrderDetails(std::ostream &out, int orderIndex) const;
    std::vector<Product> getProducts() const { return products; };
};