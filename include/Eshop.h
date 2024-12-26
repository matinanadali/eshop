#pragma once
#include "Product.h"
#include "Customer.h"
#include "Administrator.h"
#include <map>
#include <vector>
#include <iostream>
#include <fstream>

class Eshop {
    std::map<std::string, User*> users;  // Map to store users by username
    std::vector<std::pair<Product, float>> products;
    int fetchUsers();
    int fetchProducts();
    
    public:
    Eshop();
    
    // More methods to be added
};