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
  std::string measurementType;
  float amount;

public:
  Product(const std::string &title, const std::string &description,
          const std::string &category, const std::string &subcategory,
          const float &price, const std::string &measurementType, const float &amount)
      : title(title), description(description), category(category),
        subcategory(subcategory), price(price),
        measurementType(measurementType), amount(amount){};
  // void showProductDetails(float quantity);
};