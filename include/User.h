#pragma once
#include <string>
#include "Product.h"

class Eshop; // Forward declaration, in order to use "this" pointer

// Abstract User Class
class User {
    std::string username;
    std::string password;
    bool isAdmin;

    public: 
        User(const std::string &username, const std::string &password, const bool &isAdmin): username(username), password(password), isAdmin(isAdmin) {};
        // Virtual function : it exists in Customer and Administrator Class but with different functionality
        virtual void searchProduct() = 0;
        virtual void addProduct(Eshop* eshop) = 0;
        virtual void updateProduct(Eshop* eshop) = 0;
        virtual void removeProduct(Eshop* eshop) = 0;

        virtual void unavailableProducts(Eshop* eshop){}
        virtual void top5Products(Eshop* eshop){}

        virtual void makeOrder(){}
        virtual void viewOrderHistory(){}
        virtual void showCart(){}

        std::string getUsername() const { return username; };
        std::string getPassword() const { return password; };
        int getIsAdmin() const { return isAdmin ; };
        virtual ~User() {};
};