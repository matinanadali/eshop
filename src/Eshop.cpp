#include "../include/Eshop.h"
#include "../include/Customer.h"

////////////////////////// Constructor & Initialization Methods /////////////////////////////////

Eshop::Eshop(const std::string &categoriesFilePath,
             const std::string &productsFilePath,
             const std::string &usersFilePath)
    : categoriesFilePath(categoriesFilePath),
      productsFilePath(productsFilePath), usersFilePath(usersFilePath) {
  // Initialize E-shop with data from files
  fetchProducts(productsFilePath);
  fetchCategories(categoriesFilePath);

  for (const auto &[title, product] : products) {
    // Initially every product appears in 0 orders
    productsByOrder.insert({0, title});
    productOrders[title] = 0;
  }

  fetchUsers(usersFilePath);
};

void Eshop::fetchUsers(const std::string &usersFilePath) {
  std::ifstream file(usersFilePath); // Open the file

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return;
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
      Administrator* admin = new Administrator(username, password, isAdmin, this);
      users[username] = admin;
    } else {
      Customer* customer = new Customer(username, password, isAdmin, this);
      users[username] = customer;
      customer->fetchOrderHistory();
    }
  }

  file.close(); // Close the file
}

void Eshop::fetchProducts(const std::string &productsFilePath) {
  std::ifstream file(productsFilePath); // Open the file

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return;
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

  // Note discounts
  productDiscount = 0.2;
  categoryDiscount = 0.3;
  favoriteDiscount = 0.4;
}

void Eshop::fetchCategories(const std::string &categoriesFilePath) {
  std::ifstream file(categoriesFilePath); // Open the file

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return;
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

  // Read minimum amounts to get category discount
  std::string filePath = "files/discounts.txt";
  file = std::ifstream(filePath); // Open the file

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return;
  }

  for (unsigned int i = 0; i < categories.size(); i++) {
    std::string category; // Read category
    file >> category;
    
    file.ignore(); file.ignore(); file.ignore();  // ignore " @ "
    float minAmount;
    file >> minAmount;   // Read min amount

    minAmountForCategoryDiscounts[category] = minAmount;
  }
}

/////////////////////////////////////// User Registration/Login Methods //////////////////////////////////////////

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
        "with a different username? (enter option login/register/cancel): ", 
        "Invalid option. Please pick login, register or cancel: ");

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
      readStringOption({"y", "n"}, "Are you an admin user? (y/n): ", "Invalid option. Please pick y or n: ");
  isAdmin = (isAdminString == "y");

  // Create new user
  if (isAdmin) {
    users[username] = new Administrator(username, password, isAdmin, this);
  } else {
    users[username] = new Customer(username, password, isAdmin, this);
  }

  activeUser = users[username];
  std::cout << "Thanks for signing up! You are automatically logged-in as "
            << activeUser->getUsername() << "\n";
  fflush(stdout);
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
        readStringOption({"Y", "N"}, "Would you like to try again (Y/N)? ", "Invalid option. Please pick Y or N: ");
    if (option == "Y") {
      loginUser();
      return;
    } else {
      // End login process
      return;
    }
  }

  activeUser = users[username];
  std::cout << "\nWelcome " << activeUser->getUsername() << "!\n";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

/////////////////////////////////////// Menus /////////////////////////////////////

void Eshop::showMenu() {
  activeUser->displayMenu();
}

/////////////////////////////////////// Varius Functions /////////////////////////////////////

void Eshop::showProducts() {
  // Show all products
  for (auto &[title, product] : products) {
    product.showProductDetails();
  }
}

std::vector<Product> Eshop::getTop5Products() {
  std::set<std::pair<int, std::string>>::iterator productIterator =
      productsByOrder.begin();

  std::vector<Product> topProducts;
  // Get top 5 products that appear in at least one order
  for (int i = 0; i < 5 && productIterator != productsByOrder.end(); i++) {
    int numOfOrders = productIterator->first;
    // std::cout << productIterator->second << " " << numOfOrders << "\n";
    if (numOfOrders == 0)
      break; // Product does not appear in any order
    topProducts.push_back(
        products[productIterator->second]); // Add product to topProducts
    productIterator++;
  }

  return topProducts;
}

void Eshop::removeProductByTitle(const std::string &title) {
    products.erase(title);

    // Remove product from active user cart
    if (!activeUser->getIsAdmin()) {
      Customer* customer = dynamic_cast<Customer*>(activeUser);
      customer->removeProductFromCart(title);
    }
}

void Eshop::incrementProductOrders(const std::string &title) {
    int numOfOrders = productOrders[title]; // Number of orders product currently appears in
    productsByOrder.erase({numOfOrders, title});  // Remove product from set
    productOrders[title]++;  // Increment the number of orders the products appears in
    productsByOrder.insert({productOrders[title], title}); // Add the product back in set
}

///////////////////////////////////// Destructor and Data Storage ////////////////////////////

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

void Eshop::storeUsers(){
  std::ofstream file(usersFilePath); // Open the file

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return;
  }

  int size = users.size();
  int counter = 0; // To track when to print the newline character

  for (const auto &[username, User] : users) {
    counter++;
    file << User->getUsername() << "," << User->getPassword() << "," << User->getIsAdmin();
    file << (counter == size ? "" : "\n"); // print newline character only if this is not the end of the file

    if (!User->getIsAdmin()) {
      Customer* customer = dynamic_cast<Customer*>(User);
      
      // If `User` is a customer, store his order history
      customer->storeOrderHistory();
    }
  }

  if (activeUser && !activeUser->getIsAdmin()) {
    Customer* activeCustomer = dynamic_cast<Customer*>(activeUser);
    // If `activeUser` didn't complete his order, cancel it and update stock accordingly before storing data to file
    activeCustomer->emptyCart();
  }
}

Eshop::~Eshop() {
  storeUsers();
  storeProducts();

  for (const auto &[username, user] : users) {
    delete user;
  }
}