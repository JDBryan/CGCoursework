#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Utils.h"
#include <string>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

class Light {
  private:
    glm::vec3 _centre;
    float _radius;
  public:
    Light(glm::vec3 point, float radius);
    glm::vec3 getPoint();
    std::vector<glm::vec3> getAllPoints(int resolution);
};
