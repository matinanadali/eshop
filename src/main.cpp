#include "../include/Eshop.h"

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Incorrect number of command-line arguments provided.\nExample "
                 "usage:./ oop24 files /categories.txt files / products.txt "
                 "files / users.txt "
              << std::endl;
    return 1;
  }

  std::string categoriesFilePath = argv[1];
  std::string productsFilePath = argv[2];
  std::string usersFilePath = argv[3];
  
   Eshop eshop = Eshop(categoriesFilePath, productsFilePath, usersFilePath);

  return 0;
}