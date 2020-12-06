#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "DrawingWindow.h"
#include "CanvasPoint.h"
#include "Camera.h"

class ModelPoint {

  private:
    glm::vec3 _position;
    glm::vec3 _normal;
    Material _material;
    TexturePoint _texturePoint;
    bool _hasNormal = false;


  public:
    ModelPoint();
    ModelPoint(float x, float y, float z);
    ModelPoint(float x, float y, float z, Material m);

    glm::vec3 getPosition();
    glm::vec3 getNormal();
    float x();
    float y();
    float z();
    bool hasNormal();

    void setTexturePoint(float x, float y);
    void setTexturePoint(TexturePoint t);
    void setNormal(glm::vec3 normal);

    CanvasPoint project(DrawingWindow &window, Camera &camera, float scalar);

    ModelPoint operator-(ModelPoint rhs);
    friend std::ostream &operator<<(std::ostream &os, const ModelPoint &point);


};
