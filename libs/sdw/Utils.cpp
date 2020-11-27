#include "Utils.h"

std::vector<std::string> split(const std::string &line, char delimiter) {
	auto haystack = line;
	std::vector<std::string> tokens;
	size_t pos;
	while ((pos = haystack.find(delimiter)) != std::string::npos) {
		tokens.push_back(haystack.substr(0, pos));
		haystack.erase(0, pos + 1);
	}
	// Push the remaining chars onto the vector
	tokens.push_back(haystack);
	return tokens;
}

std::vector<float> interpolateSingleFloats(float from, float to, int numberOfValues) {
	std::vector<float> results;
	if (numberOfValues == 1) {
		results.push_back(from);
		return results;
	}
	float interval = (to - from) / (numberOfValues - 1);
	for (int i = 0; i < numberOfValues; i++) {
		results.push_back(from + i*interval);
	}
	return results;
}

std::vector<glm::vec3> interpolateVectors(glm::vec3 from, glm::vec3 to, int numberOfValues) {
	std::vector<glm::vec3> results;
	if (numberOfValues == 1) {
		results.push_back(from);
		return results;
	}
	std::vector<float> xVals = interpolateSingleFloats(from.x, to.x, numberOfValues);
	std::vector<float> yVals = interpolateSingleFloats(from.y, to.y, numberOfValues);
	std::vector<float> zVals = interpolateSingleFloats(from.z, to.z, numberOfValues);
	for (int i = 0; i < numberOfValues; i++) {
		results.push_back(glm::vec3(xVals[i], yVals[i], zVals[i]));
	}
	return results;
}

int randomNumber(int min, int max) {
  return rand() % (max - min) + min;
}
