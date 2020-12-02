#include "Ray.h"

Ray::Ray(glm::vec3 pVector, glm::vec3 dVector) {
  _position = pVector;
  _direction = dVector;
}

Ray::Ray(DrawingWindow &window, Camera &camera, CanvasPoint pixel) {
  _position = glm::vec3(camera.x(), camera.y(), camera.z());
  glm::vec3 pixelPosition = glm::vec3(pixel.x()-window.width/2, window.height/2-pixel.y(), camera.getFocalLength());
  _direction = (pixelPosition - _position);
}

RayTriangleIntersection Ray::findTriangleIntersection(ModelTriangle triangle, Camera camera) {
  glm::vec3 e0 = triangle.v1().getPosition() - triangle.v0().getPosition();
  glm::vec3 e1 = triangle.v2().getPosition() - triangle.v0().getPosition();
  glm::vec3 SPVector = glm::vec3(camera.x(), camera.y(), camera.z()) - triangle.v0().getPosition();
  glm::mat3 DEMatrix(-_direction, e0, e1);
  glm::vec3 possibleSolution = glm::inverse(DEMatrix) * SPVector;
  if (possibleSolution[1] > 1 || possibleSolution[1] < 0 || possibleSolution[2] > 1 || possibleSolution[2] < 0 || possibleSolution[1] + possibleSolution[2] > 1) {
    return RayTriangleIntersection();
  }
  glm::vec3 r = triangle.v0().getPosition() + (possibleSolution[1] * e0) + (possibleSolution[2] * e1);
  return RayTriangleIntersection(r, possibleSolution[0], triangle);
}
