#pragma once
#include <sstream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "ModelObject.h"
#include "Utils.h"


class Model {
  public:
    Model(std::string fileLocation, std::string filename, float scalar);
    std::map<std::string, Material> loadMaterials(std::string fileLocation, std::string filename);

    std::vector<ModelObject> getObjects();

    void drawFrame(DrawingWindow &window, Camera &camera, float scalar);
    void fill(DrawingWindow &window, Camera &camera, float scalar);


  private:
    std::vector<ModelObject> _objects;
};
