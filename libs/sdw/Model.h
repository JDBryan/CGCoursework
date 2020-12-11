#pragma once
#include <sstream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "ModelObject.h"
#include "Utils.h"
#include "Ray.h"
#include "Light.h"


class Model {
  public:
    Model(std::string fileLocation, std::string filename, float scalar);
    std::map<std::string, Material> loadMaterials(std::string fileLocation, std::string filename);

    std::vector<ModelObject> getObjects();

    RayTriangleIntersection getClosestIntersection(Ray ray, std::vector<ModelTriangle> faces);
    bool doesIntersect(Ray ray, std::vector<ModelTriangle> faces, float rayLength);
    float getBrightness(std::vector<ModelTriangle> faces, Ray cameraRay, RayTriangleIntersection cameraRayIntersection, Light light, glm::vec3 normal, std::string lightingType);

    void merge(Model secondModel);
    void drawFrame(DrawingWindow &window, Camera &camera, float scalar);
    void fill(DrawingWindow &window, Camera &camera, float scalar);
    void fillRayTracing(DrawingWindow &window, Camera &camera, float scalar, std::string lighting, std::string shading);
    void fillWithTextures(DrawingWindow &window, Camera &camera, float scalar);

  private:
    std::vector<ModelObject> _objects;
};
