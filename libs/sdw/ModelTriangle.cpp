#include "ModelTriangle.h"


ModelTriangle::ModelTriangle() = default;

ModelTriangle::ModelTriangle(ModelPoint v0, ModelPoint v1, ModelPoint v2) {
  _vertices.push_back(v0);
  _vertices.push_back(v1);
  _vertices.push_back(v2);
  _normal = glm::normalize(glm::cross(v1.getPosition() - v0.getPosition(), v2.getPosition() - v0.getPosition()));
}

ModelTriangle::ModelTriangle(ModelPoint v0, ModelPoint v1, ModelPoint v2, Material m) {
  _vertices.push_back(v0);
  _vertices.push_back(v1);
  _vertices.push_back(v2);
  _normal = glm::normalize(glm::cross(v1.getPosition() - v0.getPosition(), v2.getPosition() - v0.getPosition()));
  _material = m;
}

ModelPoint ModelTriangle::v0() {
	return _vertices[0];
}

ModelPoint ModelTriangle::v1() {
	return _vertices[1];
}

ModelPoint ModelTriangle::v2() {
	return _vertices[2];
}

Material ModelTriangle::getMaterial() {
  return _material;
}

glm::vec3 ModelTriangle::getNormal() {
  return _normal;
}

CanvasTriangle ModelTriangle::project(DrawingWindow &window, Camera &camera, float scalar) {
  CanvasPoint projectedV0 = v0().project(window, camera, scalar);
  CanvasPoint projectedV1 = v1().project(window, camera, scalar);
  CanvasPoint projectedV2 = v2().project(window, camera, scalar);
  return CanvasTriangle(projectedV0, projectedV1, projectedV2, _material);
}

void ModelTriangle::drawFrame(DrawingWindow &window, Camera &camera, float scalar) {
  project(window, camera, scalar).drawFrame(window);
}

void ModelTriangle::fill(DrawingWindow &window, Camera &camera, float scalar) {
  project(window, camera, scalar).fill(window);
}

void ModelTriangle::mapTexture(DrawingWindow &window, Camera &camera, float scalar) {
  project(window, camera, scalar).mapTexture(window);
}

std::ostream &operator<<(std::ostream &os, ModelTriangle triangle) {
	os << "(" << triangle.v0().x() << ", " << triangle.v0().y() << ", " << triangle.v0().z() << ")\n";
	os << "(" << triangle.v1().x() << ", " << triangle.v1().y() << ", " << triangle.v1().z() << ")\n";
	os << "(" << triangle.v2().x() << ", " << triangle.v2().y() << ", " << triangle.v2().z() << ")\n";
	return os;
}
