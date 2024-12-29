#include "Customer.h"
#include "../include/Eshop.h"

void Customer::fetchOrderHistory(Eshop *eshop) {
  std::string filePath = "files/order_history/" + username + "_history.txt";
  std::ifstream file(filePath); // Open the file

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return;
  }

  std::string startLine;
  while (!file.eof()) { // Reads ---CART START---
    std::getline(file, startLine);
    float amount;
    std::string title;
    float totalCost;
    std::vector<Product> products;

    // Read until we encounter the "CART END" delimiter
    while (file >> amount) {                         // Try to read the amount
      file.ignore();                                 // Ignore gap
      std::getline(file,title);                      // Read title
      Product product = eshop->getProducts()[title]; // Fetch product
      eshop->incrementProductOrders(title);          // The number of orders, `product` appears in
      product.setAmount(amount);
      products.push_back(product);
    }
    file.clear();

    std::string endCartString;
    std::getline(file, endCartString);  // Ignore ---CART END---
    std::string totalCostString;
    file >> totalCostString >> totalCostString; // Ignore "Total Cost:"
    file >> totalCost; // Read Total Cost
    file.ignore();

    // Create order and add it to order history
    Order order(products, totalCost);
    orderHistory.push_back(order);
  }
}

void Customer::addProduct(Eshop *eshop) {
  std::map<std::string, Product> products = eshop->getProducts();

  // Ask for input
  std::string title =
      readMultiWordInput(mapKeys(eshop->getProducts()),
                         "Which product would you like to add? ", "-");

  if (title == "") {
    // Product was not found
    std::cout << "Product not found.\n";
  } else {
    Product product = products[title];
    float customerAmount =
        readFloat("Enter quantity: ", 10e-6); // To avoid 0 amount
    float eshopAmount = product.getAmount();

    if (customerAmount > eshopAmount) {
      std::cout << "Product currently unavailable.\n";
    } else {
      eshop->editProductAmount(title,
                               eshopAmount - customerAmount); // Update stock
      // Set product amount and add it to cart
      product.setAmount(customerAmount);
      shoppingCart[title] = product;
    }
  }
}

void Customer::updateProduct(Eshop *eshop) {
  // Ask for input
  std::string title = readMultiWordInput(
      mapKeys(shoppingCart), "Which product would you like to update? ", "-");

  if (title == "") {
    // Product was not found
    std::cout << "Product not found in your shopping cart.\n";
  } else {
    Product product = shoppingCart[title];

    float customerOldAmount = product.getAmount();
    float customerNewAmount =
        readFloat("Enter new quantity: ", 10e-6); // To avoid 0 amount
    float eshopAmount = eshop->getProducts()[title].getAmount();

    if (customerNewAmount - customerOldAmount > eshopAmount) {
      std::cout << "Product currently unavailable.\n";
    } else {
      eshop->editProductAmount(title, eshopAmount + customerOldAmount -
                                          customerNewAmount); // Update stock
      // Set product amount and add it to cart
      product.setAmount(customerNewAmount);
      shoppingCart[title] = product;
    }
  }
}

void Customer::removeProduct(Eshop *eshop) {
  // Ask for input
  std::string title = readMultiWordInput(
      mapKeys(shoppingCart), "Which product would you like to remove? ", "-");

  if (title == "") {
    // Product was not found
    std::cout << "Product not found in your shopping cart.\n";
  } else {
    Product product = shoppingCart[title];

    float customerAmount = product.getAmount();
    float eshopAmount = eshop->getProducts()[title].getAmount();

    eshop->editProductAmount(title,
                             eshopAmount + customerAmount); // Update stock
    shoppingCart.erase(title);
  }
}

void Customer::makeOrder(Eshop *eshop) {
  float totalCost = 0;
  // Calculate total cost
  for (const auto &[title, product] : shoppingCart) {
    totalCost += product.getAmount() * product.getPrice();
    eshop->incrementProductOrders(title);
  }
  Order order = Order(mapValues(shoppingCart),
                      totalCost); // Add all products to a new order
  orderHistory.push_back(order);
  shoppingCart.clear(); // Empty cart

  std::cout << "Order Completed!\n";
}

void Customer::viewOrderHistory() {
  int orderIndex = 1;
  for (const auto &order : orderHistory) {
    // Print order to cout
    order.showOrderDetails(std::cout, orderIndex++);
    std::cout << "\n";
  }
}

void Customer::showCart() {
  std::cout << "---CART START---\n";
  for (const auto &[_, product] : shoppingCart) {
    std::cout << product.getAmount() << " " << product.getTitle() << "\n";
  }
  std::cout << "---CART END---\n";
}

void Customer::storeOrderHistory(Eshop *eshop) {
  std::string filePath = "files/order_history/" + username + "_history.txt";
  std::ofstream file(filePath);

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return;
  }
  int orderIndex = 1;
  for (const auto &order : orderHistory) {
    // Print order to file
    order.showOrderDetails(file, orderIndex++);
    if (orderIndex != (int)orderHistory.size() + 1) {
      file << "\n";
    }
  }
}