#pragma once
#include <iostream>
#include <stdio.h>
#include "Colour.h"
#include "TextureMap.h"

class Material {
  private:
    std::string _name;
    Colour _colour;
    TextureMap *_texture;
    bool _hasTexture;

  public:
    Material(std::string name);

    Colour getColour();
    TextureMap *getTexture();
    bool hasTexture();

    void setColour(Colour colour);
    void setTexture(TextureMap &texture);

  	friend std::ostream &operator<<(std::ostream &os, const Material &material);
};
