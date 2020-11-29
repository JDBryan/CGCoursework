#include "CanvasLine.h"

CanvasLine::CanvasLine() = default;

CanvasLine::CanvasLine(CanvasPoint v0, CanvasPoint v1) {
  _v0 = v0;
  _v1 = v1;
  _material = Material(Colour(0,0,0));
}

CanvasLine::CanvasLine(CanvasPoint v0, CanvasPoint v1, Material m) {
  _v0 = v0;
  _v1 = v1;
  _material = m;
}

CanvasPoint CanvasLine::v0() {
    return _v0;
}

CanvasPoint CanvasLine::v1() {
    return _v1;
}

float CanvasLine::length() {
  float xDist = _v0.x() - _v1.x();
  float yDist = _v0.y() - _v1.y();
  return std::sqrt(yDist*yDist + xDist*xDist);
}

CanvasPoint CanvasLine::findIntersectionWithY(float y) {
  if (y < std::min(_v0.y(), _v1.y()) || y > std::max(_v0.y(), _v1.y()) || _v0.y() == _v1.y()) {
    return CanvasPoint();
  } else {
    float ratio = (y - _v0.y()) / (_v1.y() - _v0.y());
    float x = _v0.x() + (_v1.x() - _v0.x()) * ratio;
    float z = _v0.z() + (_v1.z() - _v0.z()) * ratio;
    return CanvasPoint(x, y, z);
  }
}

void CanvasLine::draw(DrawingWindow &window) {
  float xDist = _v1.x() - _v0.x();
  float yDist = _v1.y() - _v0.y();

  if (length() == 0) {
    window.setPixelColour(_v0.x(), _v0.y(), _material.getColour());
  } else {
    int numberOfSteps = std::ceil(std::max(std::abs(xDist), std::abs(yDist)))+1;
    std::vector<glm::vec3> positions = interpolateVectors(_v0.getPosition(), _v1.getPosition(), numberOfSteps);
   for (int i = 0; i < numberOfSteps; i++) {
     window.setPixelColour(positions[i].x, positions[i].y, _material.getColour());
   }
  }
}

void CanvasLine::mapTexture(DrawingWindow &window, TextureMap &texture) {
  float xDist = _v1.x() - _v0.x();
  float yDist = _v1.y() - _v0.y();

  if (length() == 0) {
    window.setPixelColour(_v0.x(), _v0.y(), _material.getColour());
  } else {
    int numberOfSteps = std::ceil(std::max(std::abs(xDist), std::abs(yDist)))+1;
    std::vector<float> xTextVals = interpolateSingleFloats(_v0.getTexturePoint().x(), _v1.getTexturePoint().x(), numberOfSteps);
    std::vector<float> yTextVals = interpolateSingleFloats(_v0.getTexturePoint().y(), _v1.getTexturePoint().y(), numberOfSteps);
    std::vector<glm::vec3> positions = interpolateVectors(_v0.getPosition(), _v1.getPosition(), numberOfSteps);
   for (int i = 0; i < numberOfSteps; i++) {
     window.setPixelColour(positions[i].x, positions[i].y, texture.getColourFromPoint(xTextVals[i], yTextVals[i]));
   }
  }
}

std::ostream &operator<<(std::ostream &os, CanvasLine &line) {
	os << line.v0() << line.v1();
	return os;
}
