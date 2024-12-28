#include <iostream>
#include "Customer.h"
#include "../include/Eshop.h"

void Customer::searchProduct(){
  std::cout << "Customer Search product\n";  
}
Product Customer::addProduct(Eshop* eshop){
  std::cout << "Customer Add product\n"; 
}
void Customer::updateProduct(){
  std::cout << "Customer Update product\n"; 
}
void Customer::removeProduct(){
  std::cout << "Customer Remove product\n"; 
}
void Customer::makeOrder(){
  std::cout << "Customer Place order\n"; 
}
void Customer::viewOrderHistory(){
  std::cout << "Customer Order History\n"; 
}
void Customer::showCart(){
  std::cout << "Customer Show cart\n"; 
}