#include "General.h"

// Template function that returns the index of the first occurence of `value` in
// `vec` or -1 if the `value` does not exist
template <typename T> int indexOf(const std::vector<T> &vec, T value) {
  int size = vec.size();
  for (int i = 0; i < size; i++) {
    if (vec[i] == value)
      return i;
  }
  return -1;
}

// Helper function to transfrom the input string to lowercase
void toLowerCase(std::string &s) {
  for (auto &c : s) {
    if (c >= 'A' && c <= 'Z')
      c = c + 'a' - 'A';
  }
}

// Helper function to handle bad input
std::string readStringOption(const std::vector<std::string> &validOptions,
                             const std::string &prompt,
                             const std::string &invalidOptionPrompt) {
  // Display prompt
  std::cout << prompt;
  fflush(stdout);
  // Get user input
  std::string option;
  std::cin >> option;

  // While input is not valid, ask for new input
  while (validOptions.size() != 0 && indexOf(validOptions, option) == -1) {
    std::cout << invalidOptionPrompt;
    fflush(stdout);
    std::cin >> option;
  }

  std::cin.ignore();

  return option;
}

bool isNumber(const std::string &s) {
  int size = s.size();
  for (int i = 0; i < size; i++) {
    if (!isdigit(s[i]))
      return false;
  }
  return true;
}

int readInteger(const std::string &prompt, int minValidOption,
                int maxValidOption) {
  // Display prompt
  std::cout << prompt;
  fflush(stdout);
  // Get user input
  std::string option;
  std::cin >> option;

  // While input is not valid, ask for new input
  while (!isNumber(option) || std::stoi(option) > maxValidOption ||
         std::stoi(option) < minValidOption) {
    std::cout << "Invalid option. " << prompt;
    fflush(stdout);
    std::cin >> option;
  }

  return stoi(option);
}

bool isFloat(const std::string &str) {
  char *ptr;
  strtof(str.c_str(), &ptr);
  return (*ptr) == '\0';
}

float readFloat(const std::string &prompt, float min, float max) {
  // Display prompt
  std::cout << prompt;
  fflush(stdout);
  // Get user input
  std::string option;
  std::cin >> option;

  // While input is not valid, ask for new input
  while (!isFloat(option) || std::stof(option) > max ||
         std::stof(option) < min) {
    std::cout << "Invalid option. " << prompt;
    fflush(stdout);
    std::cin >> option;
  }

  std::cin.ignore();

  return stof(option);
}

std::string readMultiWordInput(const std::vector<std::string> &validOptions,
                               const std::string &prompt,
                               const std::string &invalidOptionPrompt) {
  std::string input;
  // Display prompt
  std::cout << prompt;

  // Get input
  std::getline(std::cin, input);

  if (validOptions.size() == 0) {
    // No valid options are given -> every input is valid
    return input;
  } else if (invalidOptionPrompt == "-") {
    // User should not be prompt to enter a new answer
    if (indexOf(validOptions, input) != -1) {
      return input;
    } else {
      return "";
    }
  } else {
    // If valid options are given, `input` does not match any of them and
    // the user should be prompt to enter a new answer (invalidOptionPrompt !=
    // "-"), ask for new input
    while (indexOf(validOptions, input) == -1) {
      std::cout << invalidOptionPrompt;
      fflush(stdout);
      std::getline(std::cin, input);
    }
  }
  return input;
}

int readNumericOption(int minOption, int maxOption) {
  std::string choicestring;
  int choice;
  do {
    std::cout << "Enter your choice: ";
    // std::cin >> choicestring;
    std::getline(std::cin, choicestring);

    if (choicestring.length() != 1 ||
        !isdigit(choicestring[0])) { // Make sure input is an one-digit integer
      std::cout << "Invalid choice! Please enter a number between " << minOption
                << " and " << maxOption << ".\n";
      continue;
    }
    choice = choicestring[0] - '0';                 // Conversion to integer
    if (choice < minOption || choice > maxOption) { // Out of bounds case
      std::cout << "Invalid choice! Please enter a number between " << minOption
                << " and " << maxOption << ".\n";
      continue;
    }
    break;
  } while (1);
  // std::cin.ignore();
  return choice;
}

std::string
readCategory(std::map<std::string, std::vector<std::string>> &categories) {
  std::string category;
  std::vector<std::string> categoriesList;

  std::cout << "Give one of the following categories: ";
  // print all categories available.
  for (const auto &category : categories) {
    std::cout << category.first << ' ';
    categoriesList.push_back(category.first);
  }

  category = readMultiWordInput(categoriesList, "\n", "Invalid category. Please choose one of the categories above: \n");

  return category;
}

std::string readSubcategory(std::vector<std::string> &subcategories) {
  std::string subcategory;

  std::cout << "Give one of the following subcategories: ";
  // print all subcategories available.
  for (const auto &subcategory : subcategories) {
    std::cout << subcategory << ' ';
  }

  subcategory = readMultiWordInput(subcategories, "\n", "Invalid subcategory. Please choose one of the "
                   "subcategories above: \n");
   
  return subcategory;
}