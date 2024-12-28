#pragma once
#include "User.h"
#include <iostream>

class Administrator : public User {
    public:
    Administrator(const std::string &username, const std::string &password, const bool &isAdmin): User(username, password, isAdmin) {};
    ~Administrator() {};

    void addProduct(Eshop* eshop);
    void updateProduct();
    void removeProduct();
    void searchProduct();

    void unavailableProducts();
    void top5Products();
};