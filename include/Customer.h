#pragma once
#include "Eshop.h"
#include "General.h"
#include "Order.h"
#include "Product.h"
#include "User.h"
#include "Cart.h"
#include <iostream>
#include <map>
#include <set>
#include <vector>

class Customer : public User {
  Cart shoppingCart;
  std::vector<Order> orderHistory;
  std::set<std::string> discountedProducts;   // Set to store which products get
                                              // the 1st type of discount
  std::set<std::string> discountedCategories; // Set to store which categories
                                              // get the 2nd type of discount

  void calculateProductDiscounts();
  void calculateCategoryDiscounts(const Order &lastOrder);
  void calculateFavoriteProductDiscount();
  void calculateDiscounts(const Order &lastOrder);
  bool canGetFavoriteProductDiscount = true;

  struct SortByAmount {
    bool operator()(const std::pair<int, std::string> &a,
                    const std::pair<int, std::string> &b) const {
      if (a.first == b.first)
        return a < b;           // Handle equality in orders
      return a.first > b.first; // Sort by the first element (amount bought) in
                                // descending order
    }
  };
  std::set<std::pair<float, std::string>, SortByAmount> productsByAmountBought;
  std::map<std::string, float> amountBought;

public:
  Customer(const std::string &username, const std::string &password,
           const bool &isAdmin, Eshop *eshop)
      : User(username, password, isAdmin, eshop){};
  std::vector<Order> getOrderHistory() const { return orderHistory; };
  void fetchOrderHistory();
  void storeOrderHistory();
  ~Customer(){};

  void addProduct();
  void updateProduct();
  void removeProduct();

  void makeOrder();
  void viewOrderHistory();
  void showCart();
  void removeProductFromCart(const std::string &title);
  void emptyCart();
};