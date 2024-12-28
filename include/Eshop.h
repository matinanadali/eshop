#pragma once
#include "Administrator.h"
#include "Customer.h"
#include "General.h"
#include "Product.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

class Eshop {
  std::string categoriesFilePath, productsFilePath, usersFilePath;
  std::map<std::string, User *> users;     // Map to store users by username
  std::map<std::string, Product> products; // Map to store products by title
  std::map<std::string, std::vector<std::string>>
      categories; // Map to store categories and their subcategories
  User *activeUser =
      nullptr; // Defined as pointer because User is an abstract class
  int fetchUsers(const std::string &usersFilePath);
  int fetchProducts(const std::string &productsFilePath);
  int fetchCategories(const std::string &categoriesFilePath);
  void loginUser();
  void registerUser();
  void showMenu();

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
  void addProduct(const Product &product) { products[product.getTitle()] = product; };
  
  // TODO: add extra logic to remove product from all open user orders
  void removeProductByTitle(const std::string &title) { products.erase(title); };
  
  std::map<std::string, Product> getProducts() const { return products; }

  ~Eshop() {
    for (const auto &[username, user] : users) {
      delete user;
    }
  }
};