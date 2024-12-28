#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <climits>
std::string readStringOption(const std::vector<std::string> &validOptions, const std::string &prompt);
int readInteger(const std::string &prompt, int min, int max = INT_MAX);
float readFloat(const std::string &prompt, float min, float max = INT_MAX);
std::string readMultiWordInput(const std::string &prompt);
int readNumericOption(int minOption, int maxOption);