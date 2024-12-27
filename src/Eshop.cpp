#include "../include/Eshop.h"

/////////////////////////////////////// Constructor & Initialization Methods ///////////////////////////////////////

Eshop::Eshop(const std::string &categoriesFilePath,
             const std::string &productsFilePath,
             const std::string &usersFilePath)
    : categoriesFilePath(categoriesFilePath),
      productsFilePath(productsFilePath), usersFilePath(usersFilePath) {
  // Initialize E-shop with data from files
  fetchUsers(usersFilePath);
  fetchProducts(productsFilePath);
};

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
    line = line.substr(username.size() +
                       1); // Discard username and the ',' character

    // Read password (until ',')
    std::string password = line.substr(0, line.find(','));
    line = line.substr(password.size() +
                       1); // Discard password and the ',' character

    // `line` is now a string of size 1 : the character that denotes whether the
    // user is an admin or not
    bool isAdmin = (line == "1");

    // Store user
    if (isAdmin) {
      users[username] = new Administrator(username, password, isAdmin);
    } else {
      users[username] = new Customer(username, password, isAdmin);
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
    line = line.substr(title.size() + 3); // Discard title

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
    float price = stof(priceString); // Cast price to float
    line = line.substr(priceString.size() + 3);

    // Read measurement unit
    std::string measurementUnit = line.substr(0, line.find(" @ "));
    bool measuredInKilos = (measurementUnit == "Kg");
    line = line.substr(measurementUnit.size() + 3);

    // Read quantity
    float quantity = stof(line);

    // Create product
    Product product = Product(title, description, category, subcategory, price,
                              measuredInKilos);
    // Add product-quantity pair to E-shop
    products.push_back({product, quantity});
  }
  file.close(); // Close the file
  return 0;
}

/////////////////////////////////////// View Information Methods ///////////////////////////////////////

// Displays all products
void Eshop::showProducts() {
  for (auto [product, quantity] : products) {
    product.showProductDetails(quantity);
  }
}

/////////////////////////////////////// User Registration/Login Methods ///////////////////////////////////////

// Processes user registration
void Eshop::registerUser() {
  std::string username, password;
  bool isAdmin;
  // Asks for username
  std::cout << "Please enter your username: ";
  std::cin >> username;

  if (users.find(username) != users.end()) {
    // Username already exists -> redirect user to login or to register with different username
    std::cout << "Username already exists. ";
    std::string option = readStringOption(
        {"login", "register", "cancel"},
        "Would you like to login or register "
        "with a different username? (enter option login/register/cancel): ");

    if (option == "login") {
        // Redirect to login
        loginUser();
        return;
    } else if (option == "register") {
        registerUser();
        return;
    } else {
        // End registration process
        return;
    }
  }

  // Ask for password
  std::cout << "Please enter your password: ";
  std::cin >> password;
  
  // Ask if user is an administrator
  std::string isAdminString = readStringOption({"y", "n"}, "Are you an admin user? (Y/N): ");
  isAdmin = (isAdminString == "y");

  // Create new user
  // User *newUser; - Should we keep this pointer?
  if (isAdmin) {
    users[username] = new Administrator(username, password, isAdmin);
  } else {
    users[username] = new Customer(username, password, isAdmin);
  }

  activeUser = users[username];
  std::cout << "Thanks for signing up! You are automatically logged-in as " << activeUser->getUsername() << "\n";

  showMenu();
}

// Processes user login
void Eshop::loginUser() {
  std::string username, password;

  // Ask for username
  std::cout << "Please enter your username: ";
  std::cin >> username;

  if (users.find(username) == users.end()) {
    // Username does not exist -> redirect user to register as a new user
    std::string option = readStringOption(
        {"yes", "no"}, "Can't find user. "
                       "Would you like to register as a new user? "
                       "(enter option yes/no): ");
    if (option == "yes") {
      // Redirect to registration
      registerUser();
      return;
    } else {
      // End login process
      return;
    }
  }

  // Ask for password
  std::cout << "Please enter your password: ";
  std::cin >> password;

  if (users[username]->getPassword() != password) {
    // Username and password don't match -> ask user to try logging in again
    std::cout << "Incorrect credentials. ";
    std::string option =
        readStringOption({"y", "n"}, "Would you like to try again (Y/N)? ");
    if (option == "y") {
      loginUser();
      return;
    } else {
      // End login process
      return;
    }
  }

  activeUser = users[username];
  std::cout << "\nWelcome " << activeUser->getUsername() << "!\n\n";

  showMenu();
}

void Eshop::showLoginPrompt() {
  std::cout << "Welcome to the e-shop!!!\n";
  std::string option =
      readStringOption({"login", "register"},
                       "Do you want to login or register? (enter option): ");

  if (option == "login") {
    loginUser();
  } else {
    registerUser();
  }
}

/////////////////////////////////////// Menus ///////////////////////////////////////
void Eshop::showMenu(){
  std::cout << "Menu:\n";
  std::cout << activeUser->getIsAdmin();
}