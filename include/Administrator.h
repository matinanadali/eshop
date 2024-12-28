#pragma once
#include "User.h"
#include <iostream>
#include "General.h"

class Administrator : public User {
    public:
    Administrator(const std::string &username, const std::string &password, const bool &isAdmin): User(username, password, isAdmin) {};
    ~Administrator() {};

    void addProduct(Eshop* eshop);
    void updateProduct(Eshop* eshop);
    void removeProduct(Eshop* eshop);
    void searchProduct();

    void unavailableProducts(Eshop* eshop);
    void top5Products(Eshop* eshop);
};