#include "Ray.h"

Ray::Ray(glm::vec3 start, glm::vec3 end) {
  _position = start;
  _direction = glm::normalize(end-start);
}

Ray::Ray(DrawingWindow &window, Camera &camera, CanvasPoint pixel) {
  _position = glm::vec3(camera.x(), camera.y(), camera.z());
  glm::vec3 pixelPosition = glm::vec3((pixel.x()-window.width/2)+camera.x(), (window.height/2-pixel.y())+camera.y(), camera.z()-camera.getFocalLength());
  _direction = glm::normalize((pixelPosition - _position) * glm::inverse(camera.getOrientation()));
}

glm::vec3 Ray::getDirection() {
  return _direction;
}

glm::vec3 Ray::getPosition() {
  return _position;
}

Ray Ray::reflect(RayTriangleIntersection point) {
   glm::vec3 normal = point.getIntersectedTriangle().getNormal();
   glm::vec3 newDirection = glm::normalize(_direction - normal * (float)(2*glm::dot(_direction, normal)));
   glm::vec3 start = point.getIntersectionPoint();
   glm::vec3 end = start + newDirection;
   return Ray(start + 0.001f * normal, end);
}

RayTriangleIntersection Ray::findTriangleIntersection(ModelTriangle triangle) {
  glm::vec3 e0 = triangle.v1().getPosition() - triangle.v0().getPosition();
  glm::vec3 e1 = triangle.v2().getPosition() - triangle.v0().getPosition();
  glm::vec3 SPVector = _position - triangle.v0().getPosition();
  glm::mat3 DEMatrix(-_direction, e0, e1);
  glm::vec3 possibleSolution = glm::inverse(DEMatrix) * SPVector;
  if (possibleSolution[1] > 1 || possibleSolution[1] < 0 || possibleSolution[2] > 1 || possibleSolution[2] < 0 || possibleSolution[1] + possibleSolution[2] > 1) {
    return RayTriangleIntersection();
  }
  glm::vec3 r = triangle.v0().getPosition() + (possibleSolution[1] * e0) + (possibleSolution[2] * e1);
  return RayTriangleIntersection(r, possibleSolution[0], possibleSolution[1], possibleSolution[2], triangle);
}
