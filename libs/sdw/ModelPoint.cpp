#include "ModelPoint.h"

ModelPoint::ModelPoint() = default;

ModelPoint::ModelPoint(float x, float y, float z) {
  _position.x = x;
  _position.y = y;
  _position.z = z;
  _material = Material(Colour(0, 0, 0));
  _texturePoint = TexturePoint(-1,-1);
  _hasNormal = false;

}

ModelPoint::ModelPoint(float x, float y, float z, Material m) {
  _position.x = x;
  _position.y = y;
  _position.z = z;
  _material = m;
  _texturePoint = TexturePoint(-1,-1);
  _hasNormal = false;
}

glm::vec3 ModelPoint::getPosition() {
  return _position;
}

glm::vec3 ModelPoint::getNormal() {
  return _normal;
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

bool ModelPoint::hasNormal() {
  return _hasNormal;
}

void ModelPoint::setTexturePoint(float x, float y) {
	_texturePoint = TexturePoint(x, y);
}

void ModelPoint::setTexturePoint(TexturePoint t) {
	_texturePoint = t;
}

void ModelPoint::setNormal(glm::vec3 normal) {
  _normal = glm::normalize(normal);
  _hasNormal = true;
}

CanvasPoint ModelPoint::project(DrawingWindow &window, Camera &camera, float scalar) {
  glm::vec3 pos = getPosition() - camera.getPosition();
  glm::vec3 orientedPoint = pos * camera.getOrientation();
  float canvasX = camera.getFocalLength() * ((-orientedPoint.x)/(orientedPoint.z));
  float canvasY = camera.getFocalLength() * (orientedPoint.y/orientedPoint.z);
  CanvasPoint point = CanvasPoint(canvasX*scalar + window.width/2, canvasY*scalar  + window.height/2, 1/orientedPoint.z, _material);
  point.setTexturePoint(_texturePoint.x(), _texturePoint.y());
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
