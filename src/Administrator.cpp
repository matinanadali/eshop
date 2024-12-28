#include "Administrator.h"
#include "../include/Eshop.h"
#include <iostream>
#include <limits>


void Administrator::addProduct(Eshop *eshop) {
  std::string title, description, category, subcategory, measurementType;
  float price, amount;

  std::cout << "Give product title: ";
  std::cin.ignore();             // to clear buffer
  std::getline(std::cin, title); // to include spaces
  std::cout << "Give product description: ";
  std::cin.ignore();             // to clear buffer
  std::getline(std::cin, title); // to include spaces
  std::cout << "Give one of the following categories: ";
  // print all categories available.
  std::map<std::string, std::vector<std::string>> &categories =
      eshop->getCategories();
  for (const auto &category : categories) {
    std::cout << category.first << ' ';
  }
  std::cout << '\n';
  do {
    std::cin >> category;
    if (categories.find(category) == categories.end())
      std::cout
          << "Invalid category. Please choose one of the categories above: \n";
  } while (categories.find(category) == categories.end());
  std::cout << "Give one of the following subcategories: ";
  // print all subcategories available.
  for (const auto &subcategory : categories[category]) {
    std::cout << subcategory << ' ';
  }
  std::cout << '\n';
  do {
    std::cin >> subcategory;
    if (std::find(categories[category].begin(), categories[category].end(),
                  subcategory) == categories[category].end()) {
      std::cout << "Invalid subcategory. Please choose one of the "
                   "subcategories above: \n";
    }
  } while (std::find(categories[category].begin(), categories[category].end(),
                     subcategory) == categories[category].end());
  std::cout << "Give product price: ";
  while (1) {
    std::cin >> price;

    if (std::cin.fail() || price < 0) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please enter a valid number: ";
    } else {
      break;
    }
  }
  std::cout << "Give measurement type[Kg/Unit]: ";
  do {
    std::cin >> measurementType;
    if (measurementType != "Kg" && measurementType != "Unit")
      std::cout << "Invalid type. Please pick Kg or Unit: ";
  } while (measurementType != "Kg" && measurementType != "Unit");
  if (measurementType == "Kg") {
    std::cout << "Give amount of Kilograms: ";
  } else {
    std::cout << "Give amount of Unit: ";
  }
  while (1) {
    std::cin >> amount;

    if (std::cin.fail() || amount < 0) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please enter a valid number: ";
    } else {
      break;
    }
  }

  Product product = Product(title, description, category, subcategory, price,
                            measurementType, amount);
  std::cout << "Product added successfully!\n";
  eshop->addProduct(product);
}

/////////////////////////////////////// Update Product Methods ///////////////////////////////////////

void updateProductTitle(Product &product) {
  std::string newTitle = readStringOption({}, "Enter new title: ");
  product.setTitle(newTitle);
}

void updateProductDescription(Product &product) {
  std::string newDescription = readStringOption({}, "Enter new description: ");
  product.setDescription(newDescription);
}

void updateProductCategory(Product &product, Eshop *eshop) {
  std::string newCategory, newSubcategory;
  std::map<std::string, std::vector<std::string>> categories = eshop->getCategories();
  for (const auto &category : categories) {
    std::cout << category.first << ' ';
  }
  std::cout << '\n';
  do {
    std::cin >> newCategory;
    if (categories.find(newCategory) == categories.end())
      std::cout
          << "Invalid category. Please choose one of the categories above: \n";
  } while (categories.find(newCategory) == categories.end());
  std::cout << "Give one of the following subcategories: ";
  // print all subcategories available.
  for (const auto &subcategory : categories[newCategory]) {
    std::cout << subcategory << ' ';
  }
  std::cout << '\n';
  do {
    std::cin >> newSubcategory;
    if (std::find(categories[newCategory].begin(), categories[newCategory].end(),
                  newSubcategory) == categories[newCategory].end()) {
      std::cout << "Invalid subcategory. Please choose one of the "
                   "subcategories above: \n";
    }
  } while (std::find(categories[newCategory].begin(), categories[newCategory].end(),
                     newSubcategory) == categories[newCategory].end());
  product.setCategory(newCategory);
  product.setSubcategory(newSubcategory);
}

void updateProductPrice(Product &product) {
  float newPrice = readFloatOption("Enter new price: ", 0);
  product.setPrice(newPrice);
}

void updateProductAmount(Product &product) {
  float newAmount = readFloatOption("Enter new amount: ", 0);
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
      readStringOption(validOptions, "Enter product title you wish to edit: ");

  // Get product
  Product oldProduct = eshop->getProducts()[title];
  Product newProduct = oldProduct;  // Create a copy of the old product

  // Read choice
  int fieldOption = readNumericOption(
      "Enter number of field you want to edit: 1.Title 2.Description "
      "3.Category and Subcategory 4.Price 5.Available Kg 6.Nothing\n", 1, 6);

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
      readStringOption(validOptions, "Enter product title you wish to remove: ");
  
  eshop->removeProductByTitle(title);
  std::cout << "Product removed!\n";
}

void Administrator::searchProduct() {
  std::cout << "Administrator Search product\n";
}

/////////////////////////////////////// View Eshop Statistics Methods ///////////////////////////////////////

void Administrator::unavailableProducts(Eshop* eshop) {
  std::map<std::string, Product> products = eshop->getProducts();
  for (const auto &[title, product] : products) {
    if (abs(product.getAmount()) < 10e-6) {
      product.showProductDetails();
    }
  }
}

void Administrator::top5Products() {
  std::cout << "Administrator top5 products\n";
}