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
        Customer(const std::string &username, const std::string &password, const bool &isAdmin): User(username, password, isAdmin) {};
        ~Customer() {};

        void searchProduct();
        void addProduct(); //const Product &product
        void updateProduct();
        void removeProduct();
        
        void makeOrder();
        void viewOrderHistory();
        void showCart();
};