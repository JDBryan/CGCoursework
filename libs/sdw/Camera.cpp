#include "Camera.h"


Camera::Camera(float x, float y, float z, float focalLength) {
  _position = glm::vec3(x, y, z);
  _orientation = glm::mat3(
    1, 0, 0,
    0, 1, 0,
    0, 0, 1
  );
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

glm::mat3 Camera::getOrientation() {
  return _orientation;
}

float Camera::getFocalLength() {
  return _focalLength;
}

void Camera::translate(float x, float y, float z) {
  glm::vec3 translation = glm::vec3(x, y, z);
  _position = _position + translation;
}

void Camera::tilt(float angle) {
  glm::mat3 rotationMatrix = glm::mat3(
    1, 0, 0,
    0, std::cos(angle), std::sin(angle),
    0, -std::sin(angle), std::cos(angle)
  );
  _orientation = _orientation * rotationMatrix;
}

void Camera::pan(float angle) {
  glm::mat3 rotationMatrix = glm::mat3(
   std::cos(angle), 0, -std::sin(angle),
   0, 1, 0,
   std::sin(angle), 0, std::cos(angle)
  );
  _orientation = _orientation * rotationMatrix;
}

void Camera::roll(float angle) {
  glm::mat3 rotationMatrix = glm::mat3(
    std::cos(angle), std::sin(angle), 0,
    -std::sin(angle), std::cos(angle), 0,
    0, 0, 1
  );
  _orientation = _orientation * rotationMatrix;
}
