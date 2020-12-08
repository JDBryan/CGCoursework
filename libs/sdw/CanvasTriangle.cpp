#include "CanvasTriangle.h"

CanvasTriangle::CanvasTriangle() = default;

CanvasTriangle::CanvasTriangle(CanvasPoint v0, CanvasPoint v1, CanvasPoint v2) {
  _vertices.push_back(v0);
  _vertices.push_back(v1);
  _vertices.push_back(v2);
  orderVerticesByHeight();
  _material = Material(Colour(0,0,0));
}

CanvasTriangle::CanvasTriangle(CanvasPoint v0, CanvasPoint v1, CanvasPoint v2, Material m) {
  _vertices.push_back(v0);
  _vertices.push_back(v1);
  _vertices.push_back(v2);
  orderVerticesByHeight();
  _material = m;
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

void CanvasTriangle::orderVerticesByHeight() {
  std::sort(_vertices.begin(), _vertices.end(), vertexYComparator);
}

void CanvasTriangle::orderVerticesByDepth() {
  std::sort(_vertices.begin(), _vertices.end(), vertexZComparator);
}

void CanvasTriangle::orderVerticesByWidth() {
  std::sort(_vertices.begin(), _vertices.end(), vertexXComparator);
}

void CanvasTriangle::drawFrame(DrawingWindow &window) {
  CanvasLine(v0(), v1(), _material).draw(window);
  CanvasLine(v1(), v2(), _material).draw(window);
  CanvasLine(v2(), v0(), _material).draw(window);
}

void CanvasTriangle::fill(DrawingWindow &window) {
  if (v2().y() < 0) return;
  orderVerticesByWidth();
  if (v0().x() >= window.width) return;
  if (v2().x() < 0) return;
  orderVerticesByHeight();

  CanvasLine line01 = CanvasLine(v0(), v1());
  CanvasLine line12 = CanvasLine(v1(), v2());
  CanvasLine line02 = CanvasLine(v0(), v2());

  for (float y = v0().y(); y < v1().y(); y++) {
    if (y >= window.height) return;
    CanvasPoint point1 = line01.findIntersectionWithY(y);
    CanvasPoint point2 = line02.findIntersectionWithY(y);
    if (point1.x() < 0) point1.setX(0);
    if (point1.x() >= window.width) point1.setX(window.width-1);
    if (point2.x() < 0) point2.setX(0);
    if (point2.x() >= window.width) point2.setX(window.width-1);
    if (point1.y() < 0) point1.setY(0);
    if (point1.y() >= window.height) point1.setY(window.height-1);
    if (point2.y() < 0) point2.setY(0);
    if (point2.y() >= window.height) point2.setY(window.height-1);
    CanvasLine line = CanvasLine(point1, point2, _material);
    line.draw(window);
  }

  for (float y = v1().y(); y < v2().y(); y++) {
    if (y >= window.height) return;
    CanvasPoint point1 = line12.findIntersectionWithY(y);
    CanvasPoint point2 = line02.findIntersectionWithY(y);
    if (point1.x() < 0) point1.setX(0);
    if (point1.x() >= window.width) point1.setX(window.width-1);
    if (point2.x() < 0) point2.setX(0);
    if (point2.x() >= window.width) point2.setX(window.width-1);
    if (point1.y() < 0) point1.setY(0);
    if (point1.y() >= window.height) point1.setY(window.height-1);
    if (point2.y() < 0) point2.setY(0);
    if (point2.y() >= window.height) point2.setY(window.height-1);
    CanvasLine line = CanvasLine(point1, point2, _material);
    line.draw(window);
  }
}

void CanvasTriangle::mapTexture(DrawingWindow &window) {
  if (v0().y() >= window.height) return;
  if (v2().y() <= 0) return;
  orderVerticesByWidth();
  if (v0().x() >= window.width) return;
  if (v2().x() <= 0) return;
  orderVerticesByHeight();
  if (!_material.hasTexture()) {
    std::cout << "no texture found for triangle" << std::endl;
  }

  float splitRatio = (v1().y() - v0().y()) / (v2().y() - v0().y());
  float xCanv = v0().x() + splitRatio * (v2().x() - v0().x());
  float yCanv = v0().y() + splitRatio * (v2().y() - v0().y());
  float zCanv = v0().z() + splitRatio * (v2().z() - v0().z());
  CanvasPoint splitPoint = CanvasPoint(xCanv, yCanv, zCanv);
  float xText = v0().getTexturePoint().x() + splitRatio * (v2().getTexturePoint().x() - v0().getTexturePoint().x());
  float yText = v0().getTexturePoint().y() + splitRatio * (v2().getTexturePoint().y() - v0().getTexturePoint().y());
  splitPoint.setTexturePoint(xText, yText);

  int topHalfSteps = (v1().y() - v0().y()) + 2;
  std::vector<glm::vec3> positions01 = interpolateVectors(v0().getPosition(), v1().getPosition(), topHalfSteps);
  std::vector<glm::vec3> tPositions01 = interpolateVectors(v0().getTextPosition(), v1().getTextPosition(), topHalfSteps);
  std::vector<glm::vec3> positions02 = interpolateVectors(v0().getPosition(), splitPoint.getPosition(), topHalfSteps);
  std::vector<glm::vec3> tPositions02 = interpolateVectors(v0().getTextPosition(), splitPoint.getTextPosition(), topHalfSteps);

  for (int i = 0; i < topHalfSteps; i++) {
    if (v0().y() + i >= window.height) return;
    CanvasPoint point1 = CanvasPoint(positions01[i]);
    CanvasPoint point2 = CanvasPoint(positions02[i]);
    if (point1.x() < 0) point1.setX(0);
    if (point1.x() >= window.width) point1.setX(window.width-1);
    if (point2.x() < 0) point2.setX(0);
    if (point2.x() >= window.width) point2.setX(window.width-1);
    if (point1.y() < 0) point1.setY(0);
    if (point1.y() >= window.height) point1.setY(window.height-1);
    if (point2.y() < 0) point2.setY(0);
    if (point2.y() >= window.height) point2.setY(window.height-1);
    point1.setTexturePoint(tPositions01[i].x, tPositions01[i].y);
    point2.setTexturePoint(tPositions02[i].x, tPositions02[i].y);
    CanvasLine line = CanvasLine(point1, point2, _material);
    line.mapTexture(window);
  }

  if (v1().y() >= window.height) return;
  orderVerticesByWidth();
  if (v1().x() >= window.width) return;
  orderVerticesByHeight();
  int bottomHalfSteps = (v2().y() - v1().y()) + 2;

  std::vector<glm::vec3> positions12 = interpolateVectors(v1().getPosition(), v2().getPosition(), bottomHalfSteps);
  std::vector<glm::vec3> tPositions12 = interpolateVectors(v1().getTextPosition(), v2().getTextPosition(), bottomHalfSteps);
  positions02 = interpolateVectors(splitPoint.getPosition(), v2().getPosition(), bottomHalfSteps);
  tPositions02 = interpolateVectors(splitPoint.getTextPosition(), v2().getTextPosition(), bottomHalfSteps);

  for (int i = 0; i < bottomHalfSteps; i++) {
    if (v1().y() + i >= window.height) return;
    CanvasPoint point1 = CanvasPoint(positions12[i]);
    CanvasPoint point2 = CanvasPoint(positions02[i]);
    if (point1.x() < 0) point1.setX(0);
    if (point1.x() >= window.width) point1.setX(window.width-1);
    if (point2.x() < 0) point2.setX(0);
    if (point2.x() >= window.width) point2.setX(window.width-1);
    if (point1.y() < 0) point1.setY(0);
    if (point1.y() >= window.height) point1.setY(window.height-1);
    if (point2.y() < 0) point2.setY(0);
    if (point2.y() >= window.height) point2.setY(window.height-1);
    point1.setTexturePoint(tPositions12[i].x, tPositions12[i].y);
    point2.setTexturePoint(tPositions02[i].x, tPositions02[i].y);
    CanvasLine line = CanvasLine(point1, point2, _material);
    line.mapTexture(window);
  }
}

bool vertexYComparator(CanvasPoint lhs, CanvasPoint rhs) {
  return lhs.y() < rhs.y();
}

bool vertexZComparator(CanvasPoint lhs, CanvasPoint rhs) {
  return lhs.z() < rhs.z();
}

bool vertexXComparator(CanvasPoint lhs, CanvasPoint rhs) {
  return lhs.x() < rhs.x();
}

CanvasPoint CanvasTriangle::getFurthestPointFromCamera() {
  orderVerticesByDepth();
  CanvasPoint result = _vertices[0];
  orderVerticesByHeight();
  return _vertices[0];
}

CanvasPoint CanvasTriangle::getClosestPointFromCamera() {
  orderVerticesByDepth();
  CanvasPoint result = _vertices[2];
  orderVerticesByHeight();
  return _vertices[0];
}

std::ostream &operator<<(std::ostream &os, const CanvasTriangle &triangle) {
	os << triangle._vertices[0] << triangle._vertices[1] << triangle._vertices[2];
	return os;
}
