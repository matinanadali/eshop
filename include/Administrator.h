#pragma once
#include "General.h"
#include "User.h"
#include <iostream>

class Administrator : public User {
  void updateProductTitle(Product &product);
  void updateProductDescription(Product &product);
  void updateProductCategory(Product &product);
  void updateProductPrice(Product &product);
  void updateProductAmount(Product &product);

public:
  Administrator(const std::string &username, const std::string &password,
                const bool &isAdmin, Eshop *eshop)
      : User(username, password, isAdmin, eshop){};
  ~Administrator(){};

  void addProduct();
  void updateProduct();
  void removeProduct();

  void unavailableProducts();
  void top5Products();
};