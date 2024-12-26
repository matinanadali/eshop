#pragma once
#include "User.h"
#include <vector>
#include "Product.h"
#include "Order.h"
#include <iostream>

class Customer : public User {
    std::vector<std::pair<Product, float>> shoppingCart;
    std::vector<Order> orderHistory;

    public:
        Customer(const std::string &username, const std::string &password): User(username, password) {};
        void addToShoppingCart(const Product &product);
        void showShoppingCart();
        void removeFromShoppingCart();
        void editShoppingCart();
        void viewProduct(const Product &product) {std::cout << "Product1\n";};
        void makeOrder();
        void viewOrderHistory();
        ~Customer() {};
};