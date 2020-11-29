#include "ModelPoint.h"

ModelPoint::ModelPoint() = default;

ModelPoint::ModelPoint(float x, float y, float z) {
  _position.x = x;
  _position.y = y;
  _position.z = z;
  _material = Material(Colour(0, 0, 0));
  _texturePoint = TexturePoint(-1,-1);
}

ModelPoint::ModelPoint(float x, float y, float z, Material m) {
  _position.x = x;
  _position.y = y;
  _position.z = z;
  _material = m;
  _texturePoint = TexturePoint(-1,-1);
}

glm::vec3 ModelPoint::getPosition() {
  return _position;
}

float ModelPoint::x() {
  return _position.x;
}

float ModelPoint::y() {
  return _position.y;
}

float ModelPoint::z() {
  return _position.z;
}

CanvasPoint ModelPoint::project(DrawingWindow &window, Camera &camera, float scalar) {
  float canvasX = camera.getFocalLength() * ((camera.x()-x())/(z()-camera.z()));
  float canvasY = camera.getFocalLength() * ((y()-camera.y())/(z()-camera.z()));
  CanvasPoint point = CanvasPoint(canvasX*scalar + window.width/2, canvasY*scalar  + window.height/2, z()-camera.z(), _material);
  return point;
}

std::ostream &operator<<(std::ostream &os, const ModelPoint &point) {
	os << "(" << point._position.x << ", "<< point._position.y << ", " << point._position.z << ")";
	return os;
}

ModelPoint ModelPoint::operator-(ModelPoint rhs) {
  glm::vec3 temp = getPosition() - rhs.getPosition();
  return ModelPoint(temp.x, temp.y, temp.z);
}
