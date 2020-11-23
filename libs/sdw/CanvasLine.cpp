#include "CanvasLine.h"

CanvasLine::CanvasLine() = default;
CanvasLine::CanvasLine(CanvasPoint v0, CanvasPoint v1, Colour c) {
  _v0 = v0;
  _v1 = v1;
  _colour = c;
}

CanvasPoint CanvasLine::v0() {
    return _v0;
}

CanvasPoint CanvasLine::v1() {
    return _v1;
}

float CanvasLine::length() {
  float xDiff = _v0.x() - _v1.x();
  float yDiff = _v0.y() - _v1.y();
  return std::sqrt(yDiff*yDiff + xDiff*xDiff);
}

void CanvasLine::draw(DrawingWindow &window) {
  float xDist = _v1.x() - _v0.x();
  float yDist = _v1.y() - _v0.y();

  if (length() == 0) {
   window.setPixelColour(_v0.x(), _v0.y(), _colour);
  } else {
   int numberOfSteps = std::ceil(std::max(std::abs(xDist), std::abs(yDist)))+1;
   std::vector<float> xVals = interpolateSingleFloats(_v0.x(), _v1.x(), numberOfSteps);
   std::vector<float> yVals = interpolateSingleFloats(_v0.y(), _v1.y(), numberOfSteps);
   std::vector<float> zVals = interpolateSingleFloats(_v0.z(), _v1.z(), numberOfSteps);
   for (int i = 0; i < numberOfSteps; i++) {
     window.setPixelColour(xVals[i], yVals[i], _colour);
   }
  }
}


std::ostream &operator<<(std::ostream &os, CanvasLine &line) {
	os << line.v0() << line.v1();
	return os;
}
