#pragma once
#include "Product.h"
#include <vector>

class Order {
    std::vector<Product> products;
    float totalCost;

    public:
    Order(const std::vector<Product> &products, float totalCost): products(products), totalCost(totalCost) {};
    void showOrderDetails(int orderIndex) const;
};