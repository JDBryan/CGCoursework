#include "Material.h"

Material::Material() {
}

Material::Material(std::string name) {
  _name = name;
  _colour = Colour(0,0,0);
  _hasTexture = false;
  _brightness = 1;
  _reflectivity = 0;

}

Material::Material(Colour colour) {
  _name = "unnamed";
  _colour = colour;
  _hasTexture = false;
  _brightness = 1;
  _reflectivity = 0;
}

Material::Material(TextureMap texture) {
  _name = "unnamed";
  _colour = Colour(0,0,0);
  _texture = texture;
  _hasTexture = true;
  _brightness = 1;
  _reflectivity = 0;
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

float Material::getReflectivity() {
  return _reflectivity;
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

void Material::setReflectivity(float reflectivity) {
  _reflectivity = reflectivity;
}

std::ostream &operator<<(std::ostream &os, const Material &material) {
  os << material._name << ": " << material._colour;
  return os;
}
