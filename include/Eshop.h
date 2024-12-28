#pragma once
#include "Administrator.h"
#include "Customer.h"
#include "Product.h"
#include "General.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

class Eshop {
  std::string categoriesFilePath, productsFilePath, usersFilePath;
  std::map<std::string, User *> users; // Map to store users by username
  std::vector<Product> products; // Vector to store products
  std::map<std::string, std::vector<std::string>> categories; // Map to store categories and their subcategories
  User* activeUser = nullptr; // Defined as pointer because User is an abstract class
  int fetchUsers(const std::string &usersFilePath);
  int fetchProducts(const std::string &productsFilePath);
  int fetchCategories(const std::string &categoriesFilePath);
  void loginUser();
  void registerUser();
  void showMenu();

public:
  // IMPORTANT: At the moment, E-shop is initialized with input data when constructed
  // Maybe we should split these and create a new init method instead
  Eshop(const std::string &categoriesFilePath,
        const std::string &productsFilePath, const std::string &usersFilePath);
  void product_push_back(const Product& product){
    products.push_back(product);
  }
  std::map<std::string, std::vector<std::string>>& getCategories(){
    return categories;
  }
  void showLoginPrompt();
  void showProducts();
};