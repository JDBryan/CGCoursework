#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Utils.h"
#include <string>
#include <iostream>

class CameraWayPoint {
  private:
    glm::vec3 _position;
    glm::vec3 _lookAt;

  public:
    CameraWayPoint(glm::vec3 position, glm::vec3 lookAt);
    glm::vec3 position();
    glm::vec3 getLookAt();
};
