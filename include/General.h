#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <climits>
#include <limits>
#include <map>
#include "Product.h"

std::string readStringOption(const std::vector<std::string> &validOptions, const std::string &prompt, const std::string &invalidOptionPrompt);
int readInteger(const std::string &prompt, int min, int max = INT_MAX);
float readFloat(const std::string &prompt, float min, float max = std::numeric_limits<std::streamsize>::max());
std::string readMultiWordInput(const std::vector<std::string> &validOptions, const std::string &prompt, const std::string &invalidOptionPrompt);
int readNumericOption(int minOption, int maxOption);
std::string readCategory(std::map<std::string, std::vector<std::string>> &map);
std::string readSubcategory(std::vector<std::string> &subcategories);