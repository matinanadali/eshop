#pragma once
#include "User.h"
#include <vector>
#include "Product.h"
#include "Order.h"
#include <iostream>
#include "Eshop.h"

class Customer : public User {
    std::vector<Product> shoppingCart;
    std::vector<Order> orderHistory;

    public:
        Customer(const std::string &username, const std::string &password, const bool &isAdmin): User(username, password, isAdmin) {};
        ~Customer() {};

        void searchProduct();
        void addProduct(Eshop* eshop);
        void updateProduct(Eshop* eshop);
        void removeProduct();
        
        void makeOrder();
        void viewOrderHistory();
        void showCart();
};