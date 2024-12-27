#pragma once
#include <string>
#include "Product.h"

// Abstract User Class
class User {
    std::string username;
    std::string password;
    bool isAdmin;

    public: 
        User(const std::string &username, const std::string &password, const bool &isAdmin): username(username), password(password), isAdmin(isAdmin) {};
        // Virtual function : it exists in Customer and Administrator Class but with different functionality
        virtual void viewProduct(const Product &product) = 0;
        void searchProduct();
        std::string getUsername() const { return username; };
        std::string getPassword() const { return password; };
        int getIsAdmin() const { return isAdmin; };
        virtual ~User() {};
};