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

class Eshop {
  std::string categoriesFilePath, productsFilePath, usersFilePath;
  std::map<std::string, User *> users;     // Map to store users by username
  std::map<std::string, Product> products; // Map to store products by title
  std::map<std::string, std::vector<std::string>>
      categories; // Map to store categories and their subcategories
  User *activeUser =
      nullptr; // Defined as pointer because User is an abstract class

  // Custom comparator to store numOfOrders-Product pairs by numOfOrders
  struct CompareByOrder {
    bool operator()(const std::pair<int, Product> &a,
                    const std::pair<int, Product> &b) const {
      return a.first > b.first; // Sort by the first element in descending order
    }
  };
  // Container that automatically sorts products based on the number of orders
  // they appear in
  std::set<std::pair<int, Product>, CompareByOrder> productsByOrder;
  int fetchUsers(const std::string &usersFilePath);
  int fetchProducts(const std::string &productsFilePath);
  int fetchCategories(const std::string &categoriesFilePath);
  void loginUser();
  void registerUser();
  void showMenu();

  void storeProducts();

public:
  // IMPORTANT: At the moment, E-shop is initialized with input data when
  // constructed Maybe we should split these and create a new init method
  // instead
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

  // TODO: add extra logic to remove product from all open user orders
  void removeProductByTitle(const std::string &title) {
    products.erase(title);
  };

  std::map<std::string, Product> getProducts() const { return products; }
  std::vector<Product> getTop5Products();

  ~Eshop();
};