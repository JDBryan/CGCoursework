#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>


std::vector<std::string> split(const std::string &line, char delimiter);
std::vector<float> interpolateSingleFloats(float from, float to, int numberOfValues);
std::vector<glm::vec3> interpolateVectors(glm::vec3 from, glm::vec3 to, int numberOfValues);
std::vector<glm::vec2> interpolateVectors(glm::vec2 from, glm::vec2 to, int numberOfValues);
int randomNumber(int min, int max);
