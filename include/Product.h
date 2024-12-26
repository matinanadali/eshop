#pragma once
#include <string>
#include <vector>
#include <iostream>

class Product {
  std::string title;
  std::string description;
  std::string category;
  std::string subcategory;
  float price;
  bool measuredInKilos;

public:
  Product(const std::string &title, const std::string &description,
          const std::string &category, const std::string &subcategory,
          float price, bool measuredInKilos)
      : title(title), description(description), category(category),
        subcategory(subcategory), price(price),
        measuredInKilos(measuredInKilos){};
  void showProductDetails(float quantity);
};