#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "DrawingWindow.h"
#include "CanvasPoint.h"
#include "Camera.h"

class ModelPoint {

  private:
    glm::vec3 _position;
    Material _material;
    TexturePoint _texturePoint;

  public:
    ModelPoint();
    ModelPoint(float x, float y, float z);
    ModelPoint(float x, float y, float z, Material m);

    glm::vec3 getPosition();
    float x();
    float y();
    float z();

    void setTexturePoint(float x, float y);

    CanvasPoint project(DrawingWindow &window, Camera &camera, float scalar);

    ModelPoint operator-(ModelPoint rhs);
    friend std::ostream &operator<<(std::ostream &os, const ModelPoint &point);


};
