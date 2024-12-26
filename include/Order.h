#pragma once
#include "Product.h"
#include <vector>

class Order {
    std::vector<std::pair<Product, float>> products;
    float totalCost;

    public:
    Order(const std::vector<std::pair<Product, float>> &products, float totalCost): products(products), totalCost(totalCost) {};
};