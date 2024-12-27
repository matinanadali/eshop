#pragma once
#include "User.h"
#include <iostream>

class Administrator : public User {
    public:
    Administrator(const std::string &username, const std::string &password, const bool &isAdmin): User(username, password, isAdmin) {};
    void viewProduct(const Product &product) {std::cout << "Product2\n";};
    ~Administrator() {};
};