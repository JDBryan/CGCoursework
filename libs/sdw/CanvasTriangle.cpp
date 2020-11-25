#include "CanvasTriangle.h"

CanvasTriangle::CanvasTriangle() = default;

CanvasTriangle::CanvasTriangle(CanvasPoint v0, CanvasPoint v1, CanvasPoint v2) {
  _vertices.push_back(v0);
  _vertices.push_back(v1);
  _vertices.push_back(v2);
  _colour = Colour(0, 0, 0);
}

CanvasTriangle::CanvasTriangle(CanvasPoint v0, CanvasPoint v1, CanvasPoint v2, Colour colour) {
  _vertices.push_back(v0);
  _vertices.push_back(v1);
  _vertices.push_back(v2);
  _colour = colour;
}

CanvasPoint &CanvasTriangle::v0() {
    return _vertices[0];
}

CanvasPoint &CanvasTriangle::v1() {
    return _vertices[1];
}

CanvasPoint &CanvasTriangle::v2() {
    return _vertices[2];
}

// void CanvasTriangle::orderVertices() {
//   std::sort(_vertices.begin(), _vertices.end(), &CanvasTriangle::vertexComparator);
// }

// bool CanvasTriangle::vertexComparator(CanvasPoint lhs, CanvasPoint rhs) {
//   return lhs.y() < rhs.y();
// }

void CanvasTriangle::drawFrame(DrawingWindow &window) {
  CanvasLine(v0(), v1(), _colour).draw(window);
  CanvasLine(v1(), v2(), _colour).draw(window);
  CanvasLine(v2(), v0(), _colour).draw(window);
}

std::ostream &operator<<(std::ostream &os, const CanvasTriangle &triangle) {
	os << triangle._vertices[0] << triangle._vertices[1] << triangle._vertices[2];
	return os;
}
