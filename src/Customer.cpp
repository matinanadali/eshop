#include "Customer.h"
#include "../include/Eshop.h"

//////////////////////////////////// Initialization //////////////////////////////////////////////

// Helper function to check if a line read from file is the begin of a cart
bool cartStart(const std::string &line) {
  std::string prefix = "---Cart";
  if (line.size() < prefix.size()) return false;
  // Match "---Cart" prefix to the `line` read
  for (unsigned int i = 0; i < prefix.size(); i++) {
    if (line[i] != prefix[i]) return false;
  }
  return true;
}

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
    if (!cartStart(startLine)) break;
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

  std::string fProductDiscountString;
  file >> fProductDiscountString >> fProductDiscountString >> fProductDiscountString;  // Ignore "Favorite Product Discount: "
  // Read if user can get the "Favorite Product Discount"
  file >> canGetFavoriteProductDiscount;

  if (orderHistory.size() > 1) {
    calculateDiscounts(eshop, orderHistory.back());
  }
}

//////////////////////////////////// Discount Calculation //////////////////////////////////////////////

void Customer::calculateProductDiscounts() {
  std::map<std::string, std::vector<int>> productOrderIndices;

  // Find the indices of the orders each product appears in
  for (unsigned int orderIndex = 0; orderIndex < orderHistory.size(); orderIndex++) {

    Order order = orderHistory[orderIndex];
    for (const auto &product: order.getProducts()) {
      // `product` appears in `orderHistory[orderIndex]`: 
      productOrderIndices[product.getTitle()].push_back(orderIndex);
    }
  }

  // For each product, check if the last three orders that contain it are consecutive
  for (const auto &[title, orderIndices] : productOrderIndices) {
    if (orderIndices.size() < 3) continue;

    int size = orderIndices.size();
    bool getsDiscount = true;

    for (int i = size - 3; i < size - 1; i++) {
      // Check that the last three order indices are consecutive
      if (orderIndices[i + 1] != orderIndices[i] + 1) {
        // If not, user does not get discount for this product
        getsDiscount = false;
      }
    }

    if (getsDiscount) {
      discountedProducts.insert(title);
    }
  }
}

void Customer::calculateCategoryDiscounts(Eshop* eshop, const Order &lastOrder) {
  std::map<std::string, float> amountOfProductsBought; // Amount of products bought from each category
  for (const auto &product : lastOrder.getProducts()) {
    amountOfProductsBought[product.getCategory()] += product.getAmount();
  }

  for (const auto &[category, _] : eshop->getCategories()) {
    // If the amount of products of this category is at least equal to the minimum amount of the category,
    // user can get this discount
    if (amountOfProductsBought[category] >= eshop->getMinAmountForCategoryDiscount()[category]) {
      discountedCategories.insert(category);
    }
  }
}

void Customer::calculateFavoriteProductDiscount(Eshop* eshop) {
  srand(time(0)); // For the random discount calculation

  // If user has already taken this discount or has less than 5 orders, he cannot take the discount
  if (!canGetFavoriteProductDiscount || orderHistory.size() < 5) return;

  for (const auto &order : orderHistory) {
    for (const auto &product : order.getProducts()) {
      float amountOfProductBought = amountBought[product.getTitle()];
      // Remove product from set
      productsByAmountBought.erase({amountOfProductBought, product.getTitle()});  
      // Increment the amount that was bought
      amountBought[product.getTitle()] += product.getAmount();  
      // Add product back to set with the updated amount bought
      productsByAmountBought.insert({amountBought[product.getTitle()], product.getTitle()}); 
    }
  }

  // Find favorite product
  std::string favoriteProduct = productsByAmountBought.begin()->second;
}

void Customer::calculateDiscounts(Eshop* eshop, const Order &lastOrder) {
  calculateProductDiscounts();
  calculateCategoryDiscounts(eshop, lastOrder);
  calculateFavoriteProductDiscount(eshop);
}

//////////////////////////////////// Add Product //////////////////////////////////////////////

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
      float eshopAmount = product.getAmount();
      if(eshopAmount == 0) {
        std::cout << "Product currently unavailable.\n";
      } else {
        float customerAmount =
          readFloat("Enter quantity: ", 10e-6); // To avoid 0 amount
        if (customerAmount > eshopAmount) {
          std::cout << "Quantity not available. Current quantity: " << eshopAmount << '\n';
        } else {
          if (shoppingCart.find(title) == shoppingCart.end()) {
            // Product not found in cart 
            // Set product amount and add it to cart
            product.setAmount(customerAmount);
            shoppingCart[title] = product;
          } else {
            // Product found in cart -> update its amount
            float currentAmount = shoppingCart[title].getAmount();
            shoppingCart[title].setAmount(currentAmount + customerAmount);
          }
          eshop->editProductAmount(title,
                                  eshopAmount - customerAmount); // Update stock
      }
    }
  }
}

//////////////////////////////////// Update Product //////////////////////////////////////////////

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

//////////////////////////////////// Remove Product //////////////////////////////////////////////

void Customer::removeProduct(Eshop *eshop) {
  // Ask for input
  std::string title = readMultiWordInput(
      mapKeys(shoppingCart), "Which product would you like to remove? ", "-");

  if (title == "") {
    // Product was not found
    std::cout << "Product not found in your shopping cart.\n";
  } else {
    removeProductFromCart(eshop, title);
  }
}

void Customer::removeProductFromCart(Eshop* eshop, const std::string &title) { 
    Product product = shoppingCart[title];

    float customerAmount = product.getAmount();
    float eshopAmount = eshop->getProducts()[title].getAmount();
    // Return product amount back to Eshop
    eshop->editProductAmount(title, eshopAmount + customerAmount); 

    // Remove product
    shoppingCart.erase(title);
};

void Customer::emptyCart(Eshop* eshop) {
  while(shoppingCart.size() > 0) {
    // Remove first product from cart until it's empty
    removeProductFromCart(eshop, shoppingCart.begin()->first);  
  }
}

//////////////////////////////////// Make Order //////////////////////////////////////////////

void Customer::makeOrder(Eshop *eshop) {
  float totalCost = 0;
  // Calculate total cost
  for (const auto &[title, product] : shoppingCart) {
    // Base price with no discounts applied
    float price = product.getPrice() * product.getAmount();
    float finalDiscount = 0;

    std::vector<std::string> discounts;

    // Find if product has any type of discount
    if (discountedProducts.find(title) != discountedProducts.end()) {
      discounts.push_back("PRODUCT");
    }
    if (discountedCategories.find(product.getCategory()) != discountedCategories.end()) {
      discounts.push_back("CATEGORY");
    }
    if (title == productsByAmountBought.begin()->second) {
      discounts.push_back("FAVORITE");
    }

    if (discounts.size() > 0) {
      // Choose a random discount to apply
      int randomDiscountIndex = rand() % discounts.size();

      if (discounts[randomDiscountIndex] == "PRODUCT") {
        // Get final discount
        finalDiscount = eshop->getProductDiscount();
        // Discount cannot be used again
        discountedProducts.erase(title);
      } else if (discounts[randomDiscountIndex] == "CATEGORY") {
        // Get final discount
        finalDiscount = eshop->getCategoryDiscount();
        // Discount cannot be used again
        discountedCategories.erase(product.getCategory());
      } else {
        // Favorite product discount
        finalDiscount = eshop->getFavoriteDiscount();
        // Disable discount
        canGetFavoriteProductDiscount = false;
      }
    }

    // Inform user
    std::cout << "Congratulations! You've earned a " << (finalDiscount * 100) 
              << "% discount on \"" << title << "\"!\n";

    // Apply discount and get final price
    totalCost += price - finalDiscount * price;

    // Mark that product appers in this order
    eshop->incrementProductOrders(title);
  }

  for (const auto &[title, product] : shoppingCart) {
      float amountOfProductBought = amountBought[product.getTitle()];
      // Remove product from set
      productsByAmountBought.erase({amountOfProductBought, product.getTitle()});  
      // Increment the amount that was bought
      amountBought[product.getTitle()] += product.getAmount();  
      // Add product back to set with the updated amount bought
      productsByAmountBought.insert({amountBought[product.getTitle()], product.getTitle()}); 
  }

  Order order = Order(mapValues(shoppingCart), totalCost); // Add all products to a new order
  orderHistory.push_back(order);

  shoppingCart.clear(); // Empty cart
  calculateDiscounts(eshop, orderHistory.back());
  std::cout << "Order Completed!\n";
}

//////////////////////////////////// Show Data Methods //////////////////////////////////////////////

void Customer::viewOrderHistory() {
  int orderIndex = 1;
  for (const auto &order : orderHistory) {
    // Print order to cout
    order.showOrderDetails(std::cout, orderIndex++);
    std::cout << "\n";
  }
}

void Customer::showCart() {
  std::cout << "\n---CART START---\n";
  float totalCost = 0;
  // Print products and calculate total cost
  for (const auto &[_, product] : shoppingCart) {
    totalCost += product.getAmount() * product.getPrice();
    std::cout << product.getAmount() << " " << product.getTitle() << "\n";
  }
  std::cout << "---CART END---\n";
  std::cout << "Total Cost: " << totalCost << '\n';
}

//////////////////////////////////// Store Data //////////////////////////////////////////////
void Customer::storeOrderHistory(Eshop *eshop) {
  // Open file
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
    file << "\n";
  }

  // Store whether user can still get his "Favorite Product" discount
  file << "Favorite Product Discount: " << canGetFavoriteProductDiscount;
}
