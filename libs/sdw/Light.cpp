#include "Light.h"

Light::Light(glm::vec3 point, float radius) {
  _centre = point;
  _radius = radius;
}

glm::vec3 Light::getPoint() {
  return _centre;
}

std::vector<glm::vec3> Light::getAllPoints(int resolution) {
  glm::vec3 backBottomLeft = glm::vec3(_centre.x - _radius, _centre.y - _radius, _centre.z + _radius);
  glm::vec3 frontBottomLeft = glm::vec3(_centre.x - _radius, _centre.y - _radius, _centre.z - _radius);
  std::vector<glm::vec3> bottomLeftEdge = interpolateVectors(frontBottomLeft, backBottomLeft, resolution);
  std::vector<glm::vec3> bottomFace;
  std::vector<glm::vec3> allPoints;
  for (glm::vec3 point: bottomLeftEdge) {
    std::vector<glm::vec3> temp = interpolateVectors(point, glm::vec3(point.x + 2*_radius, point.y, point.z), resolution);
    bottomFace.insert(bottomFace.end(), temp.begin(), temp.end());
  }

  for (glm::vec3 point: bottomFace) {
    std::vector<glm::vec3> temp = interpolateVectors(point, glm::vec3(point.x, point.y+2*_radius, point.z), resolution);
    allPoints.insert(allPoints.end(), temp.begin(), temp.end());
  }
  return allPoints;
}
