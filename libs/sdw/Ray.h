#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Model.h"
#include "RayTriangleIntersection.h"
#include "Utils.h"

class Ray {
  private:
    glm::vec3 _position;
    glm::vec3 _direction;
  public:
    Ray(glm::vec3 pVector, glm::vec3 dVector);
    Ray(DrawingWindow &window, Camera &camera, CanvasPoint pixel);

    RayTriangleIntersection findTriangleIntersection(ModelTriangle triangle, Camera camera);
};

RayTriangleIntersection getClosestIntersection(std::vector<RayTriangleIntersection> intersections);
