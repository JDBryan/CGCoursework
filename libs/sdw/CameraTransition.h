#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "CameraWayPoint.h"
#include "Utils.h"
#include "Camera.h"
#include <glm/gtx/string_cast.hpp>
#include <string>
#include <iostream>

class CameraTransition {
  private:
    std::vector<CameraWayPoint> _wayPoints;
    int _frames;
    int _currentFrame;
    std::vector<glm::vec3> _positions;
    std::vector<glm::vec3> _lookAts;

  public:
    CameraTransition(CameraWayPoint start, CameraWayPoint end, int frames);
    bool doStep(Camera &camera);
};
