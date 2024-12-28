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
        Product addProduct(Eshop* eshop);
        void updateProduct();
        void removeProduct();
        
        void makeOrder();
        void viewOrderHistory();
        void showCart();
};