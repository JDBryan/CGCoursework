#pragma once
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include "Utils.h"
#include "ModelTriangle.h"


class ModelObject {

  private:
    std::string _name;
    std::vector<ModelTriangle> _faces;
    Material _material = Material(Colour(255,0,0));

  public:
    ModelObject();
    ModelObject(std::string name);

    std::string getName();
    std::vector<ModelTriangle> getFaces();
    Material getMaterial();

    void setMaterial(Material m);
    void addFace(ModelPoint v0, ModelPoint v1, ModelPoint v2);


    void drawFrame(DrawingWindow &window, Camera &camera, float scalar);
    void fill(DrawingWindow &window, Camera &camera, float scalar);
    void mapTexture(DrawingWindow &window, Camera &camera, float scalar);
};
