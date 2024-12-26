#pragma once
#include <string>
#include "Product.h"

// Abstract User Class
class User {
    std::string username;
    std::string password;

    public: 
        User(const std::string &username, const std::string &password): username(username), password(password) {};
        // Virtual function : it exists in Customer and Administrator Class but with different functionality
        virtual void viewProduct(const Product &product) = 0;
        void searchProduct();
        std::string getPassword() const { return password; };
        virtual ~User() {};
};