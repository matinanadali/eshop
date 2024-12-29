#pragma once

#include "Administrator.h"
#include "Customer.h"
#include "General.h"
#include "Product.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <memory>

class Customer;

class Eshop {
  std::string categoriesFilePath, productsFilePath, usersFilePath;
  std::map<std::string, User *> users;     // Map to store users by username
  std::map<std::string, Product> products; // Map to store products by title
  std::map<std::string, std::vector<std::string>>
      categories; // Map to store categories and their subcategories
  User *activeUser =
      nullptr; // Defined as pointer because User is an abstract class
  
  std::map<std::string, float> minAmountForCategoryDiscounts;

  struct SortByOrder {
    bool operator()(const std::pair<int, std::string> &a,
                        const std::pair<int, std::string> &b) const {
          if (a.first == b.first) return a < b; // Handle equality in orders
          return a.first > b.first; // Sort by the first element in descending order
    }
  };
  // Container that automatically sorts products based on the number of orders
  // they appear in
  std::set<std::pair<int, std::string>, SortByOrder> productsByOrder;
  // Container that stores the number of orders each products appears in
  std::map<std::string, int> productOrders;

  void fetchUsers(const std::string &usersFilePath);
  void fetchProducts(const std::string &productsFilePath);
  void fetchCategories(const std::string &categoriesFilePath);

  void loginUser();
  void registerUser();
  void showMenu();

  void storeProducts();
  void storeUsers();

public:
  Eshop(const std::string &categoriesFilePath,
        const std::string &productsFilePath, const std::string &usersFilePath);
  std::map<std::string, std::vector<std::string>> &getCategories() {
    return categories;
  }
  void showLoginPrompt();
  void showProducts();
  void addProduct(const Product &product) {
    products[product.getTitle()] = product;
  };

  void removeProductByTitle(const std::string &title);

  void editProductAmount(const std::string &title, float newAmount) {
    products[title].setAmount(newAmount);
  };
  
  void incrementProductOrders(const std::string &title) {
    int numOfOrders = productOrders[title]; // Number of orders product currently appears in
    productsByOrder.erase({numOfOrders, title});  // Remove product from set
    productOrders[title]++;  // Increment the number of orders the products appears in
    productsByOrder.insert({productOrders[title], title}); // Add the product back in set
  }

  std::map<std::string, Product> getProducts() const { return products; }
  std::map<std::string, float> getMinAmountForCategoryDiscount() const { return minAmountForCategoryDiscounts; };
  std::vector<Product> getTop5Products();

  ~Eshop();
};

