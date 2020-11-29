#include "Material.h"

Material::Material() {
  _texture = nullptr;
}

Material::Material(std::string name) {
  _name = name;
  _texture = nullptr;
  _hasTexture = false;
}

Material::Material(Colour colour) {
  _name = "unnamed";
  _colour = colour;
  _texture = nullptr;
  _hasTexture = false;
}

Colour Material::getColour() {
  return _colour;
}

TextureMap *Material::getTexture() {
  return _texture;
}

bool Material::hasTexture() {
  return _hasTexture;
}

void Material::setColour(Colour colour) {
  _colour = colour;
}

void Material::setTexture(TextureMap &texture) {
  _hasTexture = true;
  _texture = &texture;
}

std::ostream &operator<<(std::ostream &os, const Material &material) {
  os << material._name << ": " << material._colour;
  return os;
}
