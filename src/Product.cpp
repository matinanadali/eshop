#include "Product.h"

void Product::showProductDetails(float quantity) {
    std::cout << "-----" << title << "-----\n";
    std::cout << "Description: " << description << "\n";
    std::cout << "Category: " << category << "\n";
    std::cout << "Subcategory: " << subcategory << "\n";
    std::cout << "Price per " << (measuredInKilos ? "kilo: " : "unit: ") << price << "\n";
    std::cout << "Total " << (measuredInKilos ? "kilos " : "units ") << "availiable: " << quantity << "\n\n";
}