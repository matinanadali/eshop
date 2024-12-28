#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <climits>
std::string readStringOption(const std::vector<std::string> &validOptions, const std::string &prompt);
int readNumericOption(const std::string &prompt, int minValidOption, int maxValidOption = INT_MAX);
float readFloatOption(const std::string &prompt, float minValidOption, float maxValidOption = INT_MAX);