#include "User.h"
#include "Eshop.h"

/////////////////////////////////////// Search Product Methods ///////////////////////////////////////

void User::searchProductByTitle(Eshop* eshop, const std::vector<std::string> &validTitles) {
    std::string title = readMultiWordInput(validTitles, "Select a product title: ", "-");
    if (title == "") {
        // Product was not found - terminate search
        std::cout << "Product not found.\n";
    } else {
        return eshop->getProducts()[title].showProductDetails();
    }
}

void User::searchProduct(Eshop* eshop) {

  std::cout << "Product Search Options:\n"
               "1. Search for a specific product (by title).\n"
               "2. View the products of a specific category.\n"
               "3. Show all the available products.\n";

  int fieldOption = readNumericOption(1, 3);
  // Process choice
  switch(fieldOption){
    case 1: {
      std::vector<std::string> validTitles;
      for (const auto &[title, product] : eshop->getProducts()) {
        validTitles.push_back(title);
      }
      searchProductByTitle(eshop, validTitles);
      break;
    }
    case 2: {
      std::map<std::string, std::vector<std::string>> categories = eshop->getCategories();
      std::string category = readCategory(categories);
      
      std::cout << "Results: ";
      std::map<std::string, Product> products = eshop->getProducts();
      std::vector<std::string> validTitles;
      // Find all products that belong to `category`, print them and add them to `validTitles`
      for (const auto& [title, product] : products) {
        if (product.getCategory() == category) {
            validTitles.push_back(title);
            std::cout << "\"" << title << "\" ";
        }
      }
      searchProductByTitle(eshop, validTitles);
      break;
    }
    case 3:
    {
      std::cout << "Results: ";
      std::map<std::string, Product> products = eshop->getProducts();
      std::vector<std::string> validTitles;
      // Add all products to `validTitles`
      for (const auto& [title, product] : products) {
        validTitles.push_back(title);
        std::cout << "\"" << title << "\" ";
      }
      std::cout << "\n";
      searchProductByTitle(eshop, validTitles);
      break;
    }
  }
}