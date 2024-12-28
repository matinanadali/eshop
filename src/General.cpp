#include "General.h"

// Template function that returns the index of the first occurence of `value` in `vec`
// or -1 if the `value` does not exist
template <typename T>
int indexOf(const std::vector<T> &vec, T value) {
    int size = vec.size();
    for (int i = 0; i < size; i++) {
        if (vec[i] == value) return i;
    }
    return -1;
}

// Helper function to transfrom the input string to lowercase
void toLowerCase(std::string &s) {
    for (auto &c : s) {
        if (c >= 'A' && c <= 'Z') c = c + 'a' - 'A';
    }
}

// Helper function to handle bad input
std::string readStringOption(const std::vector<std::string> &validOptions, const std::string &prompt) {
    // Display prompt
    std::cout << prompt;
    fflush(stdout);
    // Get user input
    std::string option;
    std::cin >> option;

    // While input is not valid, ask for new input
    while (validOptions.size() != 0 && indexOf(validOptions, option) == -1) {
        std::cout << "Invalid option. " << prompt;
        fflush(stdout);
        std::cin >> option;
    }

    return option;
}

bool isNumber(const std::string &s) {
    int size = s.size();
    for (int i = 0; i < size; i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

int readNumericOption(const std::string &prompt, int minValidOption, int maxValidOption) {
    // Display prompt
    std::cout << prompt;
    fflush(stdout);
    // Get user input
    std::string option;
    std::cin >> option;

    // While input is not valid, ask for new input
    while (!isNumber(option) || std::stoi(option) > maxValidOption || std::stoi(option) < minValidOption) {
        std::cout << "Invalid option. " << prompt;
        fflush(stdout);
        std::cin >> option;
    }

    return stoi(option);
}

bool isFloat(const std::string& str)
{
    char* ptr;
    strtof(str.c_str(), &ptr);
    return (*ptr) == '\0';
}

float readFloatOption(const std::string &prompt, float minValidOption, float maxValidOption) {
    // Display prompt
    std::cout << prompt;
    fflush(stdout);
    // Get user input
    std::string option;
    std::cin >> option;

    // While input is not valid, ask for new input
    while (!isFloat(option) || std::stof(option) > maxValidOption || std::stof(option) < minValidOption) {
        std::cout << "Invalid option. " << prompt;
        fflush(stdout);
        std::cin >> option;
    }

    return stof(option);
}


