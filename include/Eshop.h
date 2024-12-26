#pragma once
#include "Administrator.h"
#include "Customer.h"
#include "Product.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

class Eshop {
  std::string categoriesFilePath, productsFilePath, usersFilePath;
  std::map<std::string, User *> users; // Map to store users by username
  std::vector<std::pair<Product, float>> products;
  int fetchUsers(const std::string &usersFilePath);
  int fetchProducts(const std::string &productsFilePath);

public:
  Eshop(const std::string &categoriesFilePath,
        const std::string &productsFilePath, const std::string &usersFilePath);

  // More methods to be added
};