#include "../include/Eshop.h"
#include "../include/Customer.h"

//////////// Constructor & Initialization Methods //////////////

Eshop::Eshop(const std::string &categoriesFilePath,
             const std::string &productsFilePath,
             const std::string &usersFilePath)
    : categoriesFilePath(categoriesFilePath),
      productsFilePath(productsFilePath), usersFilePath(usersFilePath) {
  // Initialize E-shop with data from files
  fetchUsers(usersFilePath);
  fetchProducts(productsFilePath);
  fetchCategories(categoriesFilePath);

  for (const auto &[title, product] : products) {
    // Initially every product appears in 0 orders
    productsByOrder.insert({0, product});
  }
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
    std::string measurementType = line.substr(0, line.find(" @ "));
    line = line.substr(measurementType.size() + 3);

    // Read quantity
    float amount = stof(line);

    // Create product
    Product product = Product(title, description, category, subcategory, price,
                              measurementType, amount);
    // Add product to E-shop
    products[product.getTitle()] = product;
  }
  file.close(); // Close the file
  return 0;
}

int Eshop::fetchCategories(const std::string &categoriesFilePath) {
  std::ifstream file(categoriesFilePath); // Open the file

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(file, line)) { // Read the file line by line
    // Read category
    std::string category = line.substr(0, line.find(" ("));
    line = line.substr(category.size() + 2); // Discard category

    // Extract subcategories between the two parentheses
    std::string subcategoriesstring = line.substr(0, line.find(')'));

    std::vector<std::string> subcategories;

    size_t position = 0;
    while ((position = subcategoriesstring.find(" @ ")) != std::string::npos) {
      subcategories.push_back(subcategoriesstring.substr(0, position));
      subcategoriesstring = subcategoriesstring.substr(position + 3);
    }
    subcategories.push_back(subcategoriesstring); // Add the last subcategory

    categories[category] = subcategories;
  }

  file.close(); // Close the file
  return 0;
}

/////////////////////////////////////// User Registration/Login Methods
//////////////////////////////////////////

// Processes user registration
void Eshop::registerUser() {
  std::string username, password;
  bool isAdmin;
  // Asks for username
  std::cout << "Please enter your username: ";
  std::cin >> username;

  if (users.find(username) != users.end()) {
    // Username already exists -> redirect user to login or to register with
    // different username
    std::cout << "Username already exists. ";
    std::string option = readStringOption(
        {"login", "register", "cancel"},
        "Would you like to login or register "
        "with a different username? (enter option login/register/cancel): ", "Invalid option. Please pick login, register or cancel: ");

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
  std::string isAdminString =
      readStringOption({"y", "n"}, "Are you an admin user? (Y/N): ", "Invalid option. Please pick Y or N: ");
  isAdmin = (isAdminString == "y");

  // Create new user
  if (isAdmin) {
    users[username] = new Administrator(username, password, isAdmin);
  } else {
    users[username] = new Customer(username, password, isAdmin);
  }

  activeUser = users[username];
  std::cout << "Thanks for signing up! You are automatically logged-in as "
            << activeUser->getUsername() << "\n";

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
                       "(enter option yes/no): ", "Invalid option. Please pick yes or no: ");
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
        readStringOption({"y", "n"}, "Would you like to try again (Y/N)? ", "Invalid option. Please pick Y or N: ");
    if (option == "y") {
      loginUser();
      return;
    } else {
      // End login process
      return;
    }
  }

  activeUser = users[username];
  std::cout << "\nWelcome " << activeUser->getUsername() << "!\n";

  showMenu();
}

void Eshop::showLoginPrompt() {
  std::cout << "Welcome to the e-shop!!!\n";
  std::string option =
      readStringOption({"login", "register"},
                       "Do you want to login or register? (enter option): ", "Invalid option. Please pick login or register: ");
  if (option == "login") {
    loginUser();
  } else {
    registerUser();
  }
}

/////////////////////////// Menus /////////////////////////////////////
void Eshop::showMenu() {
  if (activeUser->getIsAdmin()) { // Menu for Admin

    int choice;
    do {
      std::cout << "\n---Admin Menu---\n1. Add Product\n2. Edit Product\n3. "
                   "Remove Product\n4. Search Product\n5. Show Unavailable "
                   "Products\n6. Show Top 5 Products\n7. Exit\n";

      choice = readNumericOption(1, 7);
      switch (choice) {
      case 1:
        activeUser->addProduct(this);
        break;
      case 2:
        activeUser->updateProduct(this);
        break;
      case 3:
        activeUser->removeProduct(this);
        break;
      case 4:
        activeUser->searchProduct();
        break;
      case 5:
        activeUser->unavailableProducts(this);
        break;
      case 6:
        activeUser->top5Products(this);
        break;
      case 7:
        std::cout << "Goodbye!\n";
        break;
      }

    } while (choice != 7);

  } else { // Menu for Customer
    int choice;
    do {
      choice = readNumericOption(1, 8);

      switch (choice) {
      case 1:
        activeUser->searchProduct();
        break;
      case 2:
        activeUser->addProduct(this);
        break;
      case 3:
        activeUser->updateProduct(this);
        break;
      case 4:
        activeUser->removeProduct(this);
        break;
      case 5:
        activeUser->makeOrder();
        break;
      case 6:
        activeUser->viewOrderHistory();
        break;
      case 7:
        activeUser->showCart();
        break;
      case 8:
        std::cout << "Goodbye!\n";
        break;
      }

    } while (choice != 8);
  }
}

void Eshop::showProducts() {
  for (auto &[title, product] : products) {
    product.showProductDetails();
  }
}

std::vector<Product> Eshop::getTop5Products() {
  std::set<std::pair<int, Product>>::iterator productIterator =
      productsByOrder.begin();

  std::vector<Product> topProducts;
  // Get top 5 products that appear in at least one order
  for (int i = 0; i < 5 && productIterator != productsByOrder.end(); i++) {
    int numOfOrders = productIterator->first;
    if (numOfOrders == 0)
      break; // Product does not appear in any order
    topProducts.push_back(
        productIterator->second); // Add product to topProducts
    productIterator++;
  }

  return topProducts;
}

///////////////// Destructor and Data Storage ////////////////////

void Eshop::storeProducts() {
  std::ofstream file(productsFilePath); // Open the file

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return;
  }

  int size = products.size();
  int counter = 0; // To track when to print the newline character

  for (const auto &[title, product] : products) {
    counter++;
    file << product.getTitle() << " @ " << product.getDescription() << " @ "
         << product.getCategory() << " @ " << product.getSubcategory() << " @ "
         << std::fixed << std::setprecision(2) << product.getPrice() << " @ "
         << product.getMeasurementType() << " @ " << std::fixed
         << std::setprecision(0) << product.getAmount();

    file << (counter == size ? "" : "\n"); // print newline character only if this is not the end of the file
  }
}

Eshop::~Eshop() {
  storeProducts();

  for (const auto &[username, user] : users) {
    delete user;
  }
}