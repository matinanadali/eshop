#include "Cart.h"

void Cart::addProduct(const Product &product) {
    products[product.getTitle()] = product;
}

bool Cart::isProductInCart(const std::string &title) {
    return products.find(title) != products.end();
}

void Cart::setProductAmount(const std::string &title, float amount) {
    products[title].setAmount(amount);
}

float Cart::getProductAmount(const std::string &title) {
    return products[title].getAmount();
}

void Cart::removeProduct(const std::string &title) {
    products.erase(title);
}

void Cart::show() {
    std::cout << "\n---CART START---\n";
    float totalCost = 0;
    // Print products and calculate total cost
    for (const auto &[_, product] : products) {
        totalCost += product.getAmount() * product.getPrice();
        std::cout << product.getAmount() << " " << product.getTitle() << "\n";
    }
    std::cout << "---CART END---\n";
    std::cout << "Total Cost: " << totalCost << '\n';
}