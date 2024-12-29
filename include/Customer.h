#pragma once
#include "User.h"
#include <vector>
#include "Product.h"
#include "Order.h"
#include <iostream>
#include <map>
#include "Eshop.h"
#include "General.h"

class Customer : public User {
    std::map<std::string, Product> shoppingCart;
    std::vector<Order> orderHistory;

    public:
        Customer(const std::string &username, const std::string &password, const bool &isAdmin): User(username, password, isAdmin) {};
        ~Customer() {};

        void searchProduct(Eshop* eshop);
        void addProduct(Eshop* eshop);
        void updateProduct(Eshop* eshop);
        void removeProduct(Eshop* eshop);
        
        void makeOrder();
        void viewOrderHistory();
        void showCart();
};