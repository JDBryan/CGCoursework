#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>


std::vector<std::string> split(const std::string &line, char delimiter);
std::vector<float> interpolateSingleFloats(float from, float to, int numberOfValues);
int randomNumber(int min, int max);
