#include "../include/Eshop.h"

int Eshop::fetchUsers(const std::string &usersFilePath) {
  std::ifstream file(usersFilePath); // Open the file

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(file, line)) { // Read the file line by line
    // Read username (until ',')
    std::string username = line.substr(0, line.find(','));
    line = line.substr(username.size() + 1);    // Discard username and the ',' character
    
    // Read password (until ',')
    std::string password = line.substr(0, line.find(','));
    line = line.substr(password.size() + 1);    // Discard password and the ',' character

    // `line` is now a string of size 1 : the character that denotes whether the user is an admin or not
    bool isAdmin = (line== "1");
   
    // Store user
    if (isAdmin) {
      users[username] = new Administrator(username, password);
    } else {
      users[username] = new Customer(username, password);
    }
  }

  file.close(); // Close the file
  return 0;
}

int Eshop::fetchProducts(const std::string &productsFilePath) {
    std::ifstream file(productsFilePath); // Open the file

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(file, line)) { // Read the file line by line

    // Read title
    std::string title = line.substr(0, line.find(" @ "));
    line = line.substr(title.size() + 3);   // Discard title

    // Read description
    std::string description = line.substr(0, line.find(" @ "));
    line = line.substr(description.size() + 3);

    // Read category
    std::string category = line.substr(0, line.find(" @ "));
    line = line.substr(category.size() + 3);
    
    // Read subcategory
    std::string subcategory = line.substr(0, line.find(" @ "));
    line = line.substr(subcategory.size() + 3);

    // Read price
    std::string priceString = line.substr(0, line.find(" @ "));
    float price = stof(priceString);    // Cast price to float
    line = line.substr(priceString.size() + 3);

    // Read measurement unit
    std::string measurementUnit = line.substr(0, line.find(" @ "));
    bool measuredInKilos = (measurementUnit == "Kg");
    line = line.substr(measurementUnit.size() + 3);

    // Read quantity
    float quantity = stof(line);

    // Create product
    Product product = Product(title, description, category, subcategory, price, measuredInKilos);
    // Add product-quantity pair to E-shop
    products.push_back({product, quantity});
    
  }
  file.close(); // Close the file
  return 0;
}

Eshop::Eshop(const std::string &categoriesFilePath,
        const std::string &productsFilePath, const std::string &usersFilePath)
      : categoriesFilePath(categoriesFilePath),
        productsFilePath(productsFilePath), usersFilePath(usersFilePath){
            fetchUsers(usersFilePath);
            fetchProducts(productsFilePath);
        };