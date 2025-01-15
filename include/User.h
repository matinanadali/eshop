#pragma once
#include <string>
#include "Product.h"
#include "General.h"
#include "Order.h"

class Eshop; // Forward declaration, in order to use "this" pointer

// Abstract User Class
class User {

    protected:
    std::string username;
    std::string password;
    bool isAdmin;

    // Every User is associated to exactly one eshop. 
    // The User entity is meaningless without an Eshop to apply its functionalities on.
    Eshop* eshop;   

    void searchProductByTitle(const std::vector<std::string> &validTitles);

    public: 
        User(const std::string &username, const std::string &password, const bool &isAdmin, Eshop* eshop): username(username), password(password), isAdmin(isAdmin), eshop(eshop) {};
        // Virtual function : it exists in Customer and Administrator Class but with different functionality
        void searchProduct();
        virtual void addProduct() = 0;
        virtual void updateProduct() = 0;
        virtual void removeProduct() = 0;

        virtual void unavailableProducts(){}
        virtual void top5Products(){}

        virtual void makeOrder(){}
        virtual void viewOrderHistory(){}
        virtual void showCart(){}

        std::string getUsername() const { return username; };
        std::string getPassword() const { return password; };
        int getIsAdmin() const { return isAdmin ; };
        virtual ~User() {};
};