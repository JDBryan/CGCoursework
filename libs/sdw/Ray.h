#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "RayTriangleIntersection.h"
#include "Utils.h"

class Ray {
  private:
    glm::vec3 _position;
    glm::vec3 _direction;

  public:
    Ray(glm::vec3 start, glm::vec3 end);
    Ray(DrawingWindow &window, Camera &camera, CanvasPoint pixel);

    glm::vec3 getDirection();
    glm::vec3 getPosition();

    RayTriangleIntersection findTriangleIntersection(ModelTriangle triangle);
};
