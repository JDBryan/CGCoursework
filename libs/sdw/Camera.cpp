#include "Camera.h"


Camera::Camera(float x, float y, float z, float focalLength) {
  _position = glm::vec3(x, y, z);
  _focalLength = focalLength;
}

float Camera::x() {
  return _position.x;
}

float Camera::y() {
  return _position.y;
}

float Camera::z() {
  return _position.z;
}

glm::vec3 Camera::getPosition() {
  return _position;
}

float Camera::getFocalLength() {
  return _focalLength;
}

void Camera::translate(float x, float y, float z) {
  glm::vec3 translation = glm::vec3(x, y, z);
  _position = _position + translation;
}
