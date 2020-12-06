#include "ModelObject.h"

ModelObject::ModelObject() = default;

ModelObject::ModelObject(std::string name) {
  _name = name;
  _material = Material(Colour(255,0,0));
}

std::string ModelObject::getName() {
  return _name;
}

std::vector<ModelTriangle> ModelObject::getFaces() {
  return _faces;
}

Material ModelObject::getMaterial() {
  return _material;
}

void ModelObject::setMaterial(Material m) {
  _material = m;
}

void ModelObject::addFace(ModelPoint v0, ModelPoint v1, ModelPoint v2) {
  ModelTriangle newTriangle = ModelTriangle(v0, v1, v2, _material);
  _faces.push_back(newTriangle);
}

void ModelObject::drawFrame(DrawingWindow &window, Camera &camera, float scalar) {
  for (ModelTriangle &triangle: _faces) {
    triangle.drawFrame(window, camera, scalar);
  }
}

void ModelObject::fill(DrawingWindow &window, Camera &camera, float scalar) {
  for (ModelTriangle &triangle: _faces) {
    triangle.fill(window, camera, scalar);
  }
}

void ModelObject::mapTexture(DrawingWindow &window, Camera &camera, float scalar) {
  for (ModelTriangle &triangle: _faces) {
    triangle.mapTexture(window, camera, scalar);
  }
}
