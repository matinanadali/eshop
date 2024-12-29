#pragma once
#include "User.h"
#include <vector>
#include "Product.h"
#include "Order.h"
#include <iostream>
#include <map>
#include <set>
#include "Eshop.h"
#include "General.h"

class Customer : public User {
    std::map<std::string, Product> shoppingCart;
    std::vector<Order> orderHistory;
    std::map<std::string, float> productDiscount;
    std::map<std::string, float> categoryDiscount;
    std::map<std::string, float> favoriteDiscount;

    void calculateProductDiscounts();
    void calculateCategoryDiscounts(Eshop* eshop, const Order &lastOrder);
    void calculateFavoriteProductDiscount(Eshop* eshop);
    void calculateDiscounts(Eshop* eshop, const Order &lastOrder);
    bool canGetFavoriteProductDiscount = true;

    struct SortByAmount {
    bool operator()(const std::pair<int, std::string> &a,
                        const std::pair<int, std::string> &b) const {
          if (a.first == b.first) return a < b; // Handle equality in orders
          return a.first > b.first; // Sort by the first element (amount bought) in descending order
        }
    };
    std::set<std::pair<float, std::string>, SortByAmount> productsByAmountBought;
    std::map<std::string, float> amountBought;

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
        void removeProductFromCart(Eshop* eshop, const std::string &title);
        void emptyCart(Eshop* eshop);
};