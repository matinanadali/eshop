#include "Administrator.h"
#include "../include/Eshop.h"
#include <iostream>
#include <limits>


void Administrator::addProduct(Eshop *eshop) {
  std::string title, description, category, subcategory, measurementType;
  float price, amount;

  title = readMultiWordInput("Give product title: ");
  description = readMultiWordInput("Give product description: ");
  category = readCategory(eshop->getCategories());
  subcategory = readSubcategory(eshop->getCategories()[category]);
  price = readFloat("Give product price: ", 0);
  measurementType = readStringOption({"Kg", "Unit"}, "Give measurement type[Kg/Unit]: ", "Invalid type. Please pick Kg or Unit: ");

  if (measurementType == "Kg") {
    amount = readFloat("Give amount of Kilograms: ", 0);
  } else {
    amount = readFloat("Give amount of Unit: ", 0);
  }

  Product product = Product(title, description, category, subcategory, price,
                            measurementType, amount);
  std::cout << "Product added successfully!\n";
  eshop->addProduct(product);
}

/////////////////////////////////////// Update Product Methods ///////////////////////////////////////

void updateProductTitle(Product &product) {
  std::string newTitle = readMultiWordInput("Enter new title: ");
  product.setTitle(newTitle);
}

void updateProductDescription(Product &product) {
  std::string newDescription = readMultiWordInput("Enter new description: ");
  product.setDescription(newDescription);
}

void updateProductCategory(Product &product, Eshop *eshop) {
  std::string newCategory = readCategory(eshop->getCategories());
  std::string newSubcategory = readSubcategory(eshop->getCategories()[newCategory]);
  product.setCategory(newCategory);
  product.setSubcategory(newSubcategory);
}

void updateProductPrice(Product &product) {
  float newPrice = readFloat("Enter new price: ", 0);
  product.setPrice(newPrice);
}

void updateProductAmount(Product &product) {
  float newAmount = readFloat("Enter new amount: ", 0);
  product.setAmount(newAmount);
}

// Main Update Product Method
void Administrator::updateProduct(Eshop *eshop) {
  // eshop->showProducts();
  std::string title;

  std::vector<std::string> validOptions;  // Vector of all product titles in eshop
  for (const auto &[title, product] : eshop->getProducts()) {
    validOptions.push_back(title);
  }

  // Read title
  title =
      readStringOption(validOptions, "Enter product title you wish to edit: ", "Product not found. Please enter a different product title: ");

  // Get product
  Product oldProduct = eshop->getProducts()[title];
  Product newProduct = oldProduct;  // Create a copy of the old product

  // Read choice
  std::cout <<  "Enter number of field you want to edit: 1.Title 2.Description "
      "3.Category and Subcategory 4.Price 5.Available Kg 6.Nothing\n";
  int fieldOption = readNumericOption(1, 6);

  // Process choice
  switch(fieldOption) {
    case 1:
      updateProductTitle(newProduct);
      break;
    case 2:
      updateProductDescription(newProduct);
      break;
    case 3:
      updateProductCategory(newProduct, eshop);
      break;
    case 4:
      updateProductPrice(newProduct);
      break;
    case 5:
      updateProductAmount(newProduct);
      break;
    case 6:
      break;
  }

 // Remove old product
 eshop->removeProductByTitle(title);
 // Add new product
 eshop->addProduct(newProduct);
 std::cout << "Product updated!\n";
  // eshop->showProducts();
}

/////////////////////////////////////// Remove Product Methods ///////////////////////////////////////

void Administrator::removeProduct(Eshop *eshop) {
  std::string title;

  std::vector<std::string> validOptions;  // Vector of all product titles in eshop
  for (const auto &[title, product] : eshop->getProducts()) {
    validOptions.push_back(title);
  }

  // Read title
  title =
      readStringOption(validOptions, "Enter product title you wish to remove: ", "Product not found. Please enter a different product title: ");
  
  eshop->removeProductByTitle(title);
  std::cout << "Product removed!\n";
}

/////////////////////////////////////// Search Product Methods ///////////////////////////////////////

void Administrator::searchProduct(Eshop* eshop) {

  std::string title;
  title = readTitle_empty(eshop->getProducts()); //Title is either a valid title or ""
  
  std::string category;
  category = readCategory_empty(eshop->getCategories()); //Category is either a valid category or ""

  std::string subcategory;
  if(category != ""){ //Ask for subcategory, only if category exists
    subcategory = readSubcategory_empty(eshop->getCategories()[category]); //SUbcategory is either a valid subcategory or ""
    std::cout<<":"<<subcategory<<":\n";
  }

  if(title != ""){
    std::cout<<"showProduct(title)\n";
  }
  else if(category != ""){
    if(subcategory != ""){
      std::cout<<"showSubcategory(subcategory)\n";
    }
    else{
      std::cout<<"showCategory(category)\n";
    }
  }
  else{
    std::cout<<"showProducts()\n";
  }
  
}

/////////////////////////////////////// View Eshop Statistics Methods ///////////////////////////////////////

void Administrator::unavailableProducts(Eshop* eshop) {
  std::map<std::string, Product> products = eshop->getProducts();
  for (const auto &[title, product] : products) {
    // Equality check for floating point numbers
    if (abs(product.getAmount()) < 10e-6) {
      product.showProductDetails();
    }
  }
}

void Administrator::top5Products(Eshop* eshop) {
  std::vector<Product> topProducts = eshop->getTop5Products();

  if (topProducts.size() < 5) {
    // No products have been purchased in any order
    std::cout << "Not enough orders were made.\n";
  } else {
    for (const Product &product : topProducts) {
      product.showProductDetails();
    }
  }
}