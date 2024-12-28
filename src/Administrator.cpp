#include <iostream>
#include "Administrator.h"
#include "../include/Eshop.h"
#include <limits>

void Administrator::addProduct(Eshop* eshop){
  std::string title, description, category, subcategory, measurementType;
  float price, amount;

  std::cout << "Give product title: ";
  std::cin.ignore(); // to clear buffer
  std::getline(std::cin, title); // to include spaces
  std::cout << "Give product description: ";
  std::cin.ignore(); // to clear buffer
  std::getline(std::cin, title); // to include spaces
  std::cout << "Give one of the following categories: ";
  // print all categories available.
  std::map<std::string, std::vector<std::string>>& categories = eshop->getCategories();
  for(const auto& category : categories){
    std::cout << category.first << ' ';
  }
  std::cout << '\n';
  do{
    std::cin >> category;
    if(categories.find(category) == categories.end()) std::cout << "Invalid category. Please choose one of the categories above: \n";
  } while(categories.find(category) == categories.end());
  std::cout << "Give one of the following subcategories: ";
  // print all subcategories available.
  for(const auto& subcategory : categories[category]){
    std::cout << subcategory << ' ';
  }
  std::cout << '\n';
  do{
    std::cin >> subcategory;
    if(std::find(categories[category].begin(), categories[category].end(), subcategory) == categories[category].end()){
      std::cout << "Invalid subcategory. Please choose one of the subcategories above: \n";
    }
  } while(std::find(categories[category].begin(), categories[category].end(), subcategory) == categories[category].end());
  std::cout << "Give product price: ";
  while(1){
    std::cin >> price;

    if(std::cin.fail() || price < 0){
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please enter a valid number: ";
    }
    else{
      break;
    }
  }
  std::cout << "Give measurement type[Kg/Unit]: ";
  do{
    std::cin >> measurementType;
    if(measurementType != "Kg" && measurementType != "Unit") std::cout << "Invalid type. Please pick Kg or Unit: ";
  } while(measurementType != "Kg" && measurementType != "Unit");
  if(measurementType == "Kg"){
    std::cout << "Give amount of Kilograms: ";
  }
  else{
    std::cout << "Give amount of Unit: ";
  }
  while(1){
    std::cin >> amount;

    if(std::cin.fail() || amount < 0){
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please enter a valid number: ";
    }
    else{
      break;
    }
  }

  Product product = Product(title, description, category, subcategory, price, measurementType, amount);
  eshop->product_push_back(product);

std::cout << "Product added successfully!\n";
}

void Administrator::updateProduct(){
  std::cout << "Administrator Update product\n"; 
}

void Administrator::removeProduct(){
  std::cout << "Administrator Remove product\n"; 
}

void Administrator::searchProduct(){
  std::cout << "Administrator Search product\n";  
}

void Administrator::unavailableProducts(){
  std::cout << "Administrator unavailable products\n";
}

void Administrator::top5Products(){
  std::cout << "Administrator top5 products\n";
}