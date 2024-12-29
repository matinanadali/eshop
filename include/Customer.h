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
        std::vector<Order> getOrderHistory() const {return orderHistory;};
        void fetchOrderHistory(Eshop* eshop);
        void storeOrderHistory(Eshop* eshop);
        ~Customer() {};

        void addProduct(Eshop* eshop);
        void updateProduct(Eshop* eshop);
        void removeProduct(Eshop* eshop);
        
        void makeOrder(Eshop* eshop);
        void viewOrderHistory();
        void showCart();
        void removeProductFromCart(const std::string &title) { shoppingCart.erase(title); };
};