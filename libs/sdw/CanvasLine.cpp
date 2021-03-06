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
    window.setPixelColour(_v0.x(), _v0.y(), _v0.z(), _material.getColour());
  } else {
    int numberOfSteps = std::ceil(std::max(std::abs(xDist), std::abs(yDist)))+1;
    std::vector<glm::vec3> positions = interpolateVectors(_v0.getPosition(), _v1.getPosition(), numberOfSteps);
    for (int i = 0; i < numberOfSteps; i++) {
      window.setPixelColour(positions[i].x, positions[i].y, positions[i].z, _material.getColour());
    }
  }
}

void CanvasLine::mapTexture(DrawingWindow &window) {
  float xDist = _v1.x() - _v0.x();
  float yDist = _v1.y() - _v0.y();
  if (length() == 0) {
    window.setPixelColour(_v0.x(), _v0.y(), _v0.z(), _material.getTexture().getColourFromPoint(_v0.getTexturePoint().x(), _v0.getTexturePoint().y()));
  } else {
    int numberOfSteps = std::ceil(std::max(std::abs(xDist), std::abs(yDist)))+1;
    std::vector<glm::vec2> textVals = interpolateVectors(_v0.getTexturePoint().getPosition(), _v1.getTexturePoint().getPosition(), numberOfSteps);
    std::vector<glm::vec3> positions = interpolateVectors(_v0.getPosition(), _v1.getPosition(), numberOfSteps);
    for (int i = 0; i < numberOfSteps; i++) {
      window.setPixelColour(positions[i].x, positions[i].y, positions[i].z, _material.getTexture().getColourFromPoint(textVals[i].x, textVals[i].y));
    }
  }
}

std::ostream &operator<<(std::ostream &os, CanvasLine &line) {
	os << line.v0() << line.v1();
	return os;
}
