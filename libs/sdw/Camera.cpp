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

void Camera::setPosition(glm::vec3 position) {
  std::cout << "setting position" << std::endl;
  _position = position;
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

void Camera::lookAt(glm::vec3 pos) {
    glm::vec3 forward = glm::normalize(glm::vec3(_position - pos));
    glm::vec3 right = glm::cross(glm::vec3(0, 1, 0), forward);
    glm::vec3 up = glm::cross(forward, right);
    _orientation[0] = right;
    _orientation[1] = up;
    _orientation[2] = forward;
}

void Camera::orbitX(float angle) {
  glm::mat3 rotationMatrix = glm::mat3(
    1, 0, 0,
    0, std::cos(angle), std::sin(angle),
    0, -std::sin(angle), std::cos(angle)
  );
  _position = _position * rotationMatrix;
  lookAt(glm::vec3(0,0,0));
}

void Camera::orbitY(float angle) {
  glm::mat3 rotationMatrix = glm::mat3(
   std::cos(angle), 0, -std::sin(angle),
   0, 1, 0,
   std::sin(angle), 0, std::cos(angle)
  );
  _position = _position * rotationMatrix;
  lookAt(glm::vec3(0,0,0));
}

void Camera::orbitZ(float angle) {
  glm::mat3 rotationMatrix = glm::mat3(
    std::cos(angle), std::sin(angle), 0,
    -std::sin(angle), std::cos(angle), 0,
    0, 0, 1
  );
  _position = _position * rotationMatrix;
  lookAt(glm::vec3(0,0,0));
}
