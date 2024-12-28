#include "Product.h"
// Testing-Debugging function
void Product::showProductDetails() {
    std::cout << "-----" << title << "-----\n";
    std::cout << "Description: " << description << "\n";
    std::cout << "Category: " << category << "\n";
    std::cout << "Subcategory: " << subcategory << "\n";
    std::cout << "Price per " << (measurementType == "Kg" ? "kilo: " : "unit: ") << price << "\n";
    std::cout << "Total " << (measurementType == "Kg" ? "kilos " : "units ") << "availiable: " << amount << "\n\n";
}