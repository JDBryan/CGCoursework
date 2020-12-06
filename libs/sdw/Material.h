#pragma once
#include <iostream>
#include <stdio.h>
#include "Colour.h"
#include "TextureMap.h"

class Material {
  private:
    std::string _name;
    Colour _colour;
    TextureMap _texture;
    float _brightness;
    bool _hasTexture;
    float _reflectivity;

  public:
    Material();
    Material(std::string name);
    Material(Colour colour);
    Material(TextureMap texture);

    std::string getName();
    Colour getColour();
    TextureMap getTexture();
    float getReflectivity();
    bool hasTexture();

    void setBrightness(float brightness);
    void setColour(Colour colour);
    void setTexture(TextureMap texture);
    void setReflectivity(float reflectivity);

  	friend std::ostream &operator<<(std::ostream &os, const Material &material);
};
