#include "Material.h"

Material::Material() {
}

Material::Material(std::string name) {
  _name = name;
  _colour = Colour(0,0,0);
  _hasTexture = false;
  _brightness = 1;
}

Material::Material(Colour colour) {
  _name = "unnamed";
  _colour = colour;
  _hasTexture = false;
  _brightness = 1;
}

Material::Material(TextureMap texture) {
  _name = "unnamed";
  _colour = Colour(0,0,0);
  _texture = texture;
  _hasTexture = true;
  _brightness = 1;
}

std::string Material::getName() {
  return _name;
}

Colour Material::getColour() {
  return _colour.intensity(_brightness);
}

TextureMap Material::getTexture() {
  return _texture;
}

bool Material::hasTexture() {
  return _hasTexture;
}

void Material::setColour(Colour colour) {
  _colour = colour;
}

void Material::setTexture(TextureMap texture) {
  _hasTexture = true;
  _texture = texture;
}

void Material::setBrightness(float brightness) {
    _brightness = brightness;
}

std::ostream &operator<<(std::ostream &os, const Material &material) {
  os << material._name << ": " << material._colour;
  return os;
}
