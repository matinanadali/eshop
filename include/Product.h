#pragma once
#include <iostream>
#include <string>
#include <vector>

class Product {
  std::string title;
  std::string description;
  std::string category;
  std::string subcategory;
  float price;
  std::string measurementType; // "Kg" or "Unit"
  float amount;

public:
  Product() {};
  Product(const std::string &title, const std::string &description,
          const std::string &category, const std::string &subcategory,
          const float &price, const std::string &measurementType,
          const float &amount)
      : title(title), description(description), category(category),
        subcategory(subcategory), price(price),
        measurementType(measurementType), amount(amount){};
  Product(const Product &other)
        : title(other.title), description(other.description),
          category(other.category), subcategory(other.subcategory),
          price(other.price), measurementType(other.measurementType),
          amount(other.amount) {}
  void showProductDetails();
  std::string getTitle() const { return title; };
  void setTitle(const std::string &title) { this->title = title; };
  void setDescription(const std::string &description) { this->description = description; };
  void setCategory(const std::string &category) { this->category = category; };
  void setSubcategory(const std::string &subcategory) { this->subcategory = subcategory; };
  void setPrice(float newPrice) { this->price = newPrice; };
  void setAmount(float newAmount) { this->amount = newAmount; };


};