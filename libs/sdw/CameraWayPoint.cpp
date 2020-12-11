#include "CameraWayPoint.h"

CameraWayPoint::CameraWayPoint(glm::vec3 position, glm::vec3 lookAt) {
  _position = position;
  _lookAt = lookAt;
}

glm::vec3 CameraWayPoint::position() {
  return _position;
}

glm::vec3 CameraWayPoint::getLookAt() {
  return _lookAt;
}
