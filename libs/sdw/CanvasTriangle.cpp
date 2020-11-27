#include "CanvasTriangle.h"

CanvasTriangle::CanvasTriangle() = default;

CanvasTriangle::CanvasTriangle(CanvasPoint v0, CanvasPoint v1, CanvasPoint v2) {
  _vertices.push_back(v0);
  _vertices.push_back(v1);
  _vertices.push_back(v2);
  orderVertices();
  _colour = Colour(0, 0, 0);
}

CanvasTriangle::CanvasTriangle(CanvasPoint v0, CanvasPoint v1, CanvasPoint v2, Colour colour) {
  _vertices.push_back(v0);
  _vertices.push_back(v1);
  _vertices.push_back(v2);
  orderVertices();
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

void CanvasTriangle::orderVertices() {
  std::sort(_vertices.begin(), _vertices.end(), vertexComparator);
}

void CanvasTriangle::drawFrame(DrawingWindow &window) {
  CanvasLine(v0(), v1(), _colour).draw(window);
  CanvasLine(v1(), v2(), _colour).draw(window);
  CanvasLine(v2(), v0(), _colour).draw(window);
}

void CanvasTriangle::fill(DrawingWindow &window) {
  CanvasLine line01 = CanvasLine(v0(), v1());
  CanvasLine line12 = CanvasLine(v1(), v2());
  CanvasLine line02 = CanvasLine(v0(), v2());

  for (float y = v0().y(); y < v1().y(); y++) {
    CanvasPoint point1 = line01.findIntersectionWithY(y);
    CanvasPoint point2 = line02.findIntersectionWithY(y);
    CanvasLine line = CanvasLine(point1, point2, _colour);
    line.draw(window);
  }

  for (float y = v1().y(); y < v2().y(); y++) {
    CanvasPoint point1 = line12.findIntersectionWithY(y);
    CanvasPoint point2 = line02.findIntersectionWithY(y);
    CanvasLine line = CanvasLine(point1, point2, _colour);
    line.draw(window);
  }
}

void CanvasTriangle::mapTexture(DrawingWindow &window, TextureMap &texture) {
  CanvasLine line01 = CanvasLine(v0(), v1());
  CanvasLine line12 = CanvasLine(v1(), v2());
  CanvasLine line02 = CanvasLine(v0(), v2());
  if (line01.length() < 1 || line12.length() < 1 || line02.length() < 1) {
    return;
  }

  float splitRatio = (v1().y() - v0().y()) / (v2().y() - v0().y());
  float xText = v0().getTexturePoint().x() + splitRatio * (v2().getTexturePoint().x() - v0().getTexturePoint().x());
  float yText = v0().getTexturePoint().y() + splitRatio * (v2().getTexturePoint().y() - v0().getTexturePoint().y());
  TexturePoint splitTextPoint = TexturePoint(xText, yText);
  float xCanv = v0().x() + splitRatio * (v2().x() - v0().x());
  float yCanv = v0().y() + splitRatio * (v2().y() - v0().y());
  CanvasPoint splitCanvasPoint = CanvasPoint(xCanv, yCanv, 0);

  int topHalfSteps = v1().y() - v0().y();
  std::vector<float> xVals01 = interpolateSingleFloats(v0().x(), v1().x(), topHalfSteps);
  std::vector<float> yVals01 = interpolateSingleFloats(v0().y(), v1().y(), topHalfSteps);
  std::vector<float> xTextVals01 = interpolateSingleFloats(v0().getTexturePoint().x(), v1().getTexturePoint().x(), topHalfSteps);
  std::vector<float> yTextVals01 = interpolateSingleFloats(v0().getTexturePoint().y(), v1().getTexturePoint().y(), topHalfSteps);

  std::vector<float> xVals02 = interpolateSingleFloats(v0().x(), splitCanvasPoint.x(), topHalfSteps);
  std::vector<float> yVals02 = interpolateSingleFloats(v0().y(), splitCanvasPoint.y(), topHalfSteps);
  std::vector<float> xTextVals02 = interpolateSingleFloats(v0().getTexturePoint().x(), splitTextPoint.x(), topHalfSteps);
  std::vector<float> yTextVals02 = interpolateSingleFloats(v0().getTexturePoint().y(), splitTextPoint.y(), topHalfSteps);

  for (int i = 0; i < topHalfSteps; i++) {
    CanvasPoint point1 = CanvasPoint(xVals01[i], yVals01[i], 0);
    CanvasPoint point2 = CanvasPoint(xVals02[i], yVals02[i], 0);
    point1.setTexturePoint(xTextVals01[i], yTextVals01[i]);
    point2.setTexturePoint(xTextVals02[i], yTextVals02[i]);
    CanvasLine line = CanvasLine(point1, point2, 0);
    line.mapTexture(window, texture);
  }

  int bottomHalfSteps = v2().y() - v1().y();
  std::vector<float> xVals12 = interpolateSingleFloats(v1().x(), v2().x(), bottomHalfSteps);
  std::vector<float> yVals12 = interpolateSingleFloats(v1().y()-1, v2().y(), bottomHalfSteps);
  std::vector<float> xTextVals12 = interpolateSingleFloats(v1().getTexturePoint().x(), v2().getTexturePoint().x(), bottomHalfSteps);
  std::vector<float> yTextVals12 = interpolateSingleFloats(v1().getTexturePoint().y(), v2().getTexturePoint().y(), bottomHalfSteps);

  std::vector<float> botXVals02 = interpolateSingleFloats(splitCanvasPoint.x(), v2().x(), bottomHalfSteps);
  std::vector<float> botYVals02 = interpolateSingleFloats(splitCanvasPoint.y()-1, v2().y(), bottomHalfSteps);
  std::vector<float> botXTextVals02 = interpolateSingleFloats(splitTextPoint.x(), v2().getTexturePoint().x(),  bottomHalfSteps);
  std::vector<float> botYTextVals02 = interpolateSingleFloats(splitTextPoint.y(), v2().getTexturePoint().y(),  bottomHalfSteps);

  for (int i = 0; i < bottomHalfSteps; i++) {
    CanvasPoint point1 = CanvasPoint(xVals12[i], yVals12[i], 0);
    CanvasPoint point2 = CanvasPoint(botXVals02[i], botYVals02[i], 0);
    point1.setTexturePoint(xTextVals12[i], yTextVals12[i]);
    point2.setTexturePoint(botXTextVals02[i], botYTextVals02[i]);
    CanvasLine line = CanvasLine(point1, point2, 0);
    line.mapTexture(window, texture);
  }

  // for (int y = v0().y(); y < v1().y(); y++) {
  //   float ratio01 = (y - v0().y()) / (v1().y() - v0().y());
  //   float ratio02 = (y - v0().y()) / (v2().y() - v0().y());
  //   float xText01 = v0().getTexturePoint().x() + ratio01*(v1().getTexturePoint().x() - v0().getTexturePoint().x());
  //   float yText01 = v0().getTexturePoint().y() + ratio01*(v1().getTexturePoint().y() - v0().getTexturePoint().y());
  //   float xText02 = v0().getTexturePoint().x() + ratio02*(v2().getTexturePoint().x() - v0().getTexturePoint().x());
  //   float yText02 = v0().getTexturePoint().y() + ratio02*(v2().getTexturePoint().y() - v0().getTexturePoint().y());
  //   CanvasPoint point1 = line01.findIntersectionWithY(y);
  //   point1.setTexturePoint(xText01, yText01);
  //   CanvasPoint point2 = line02.findIntersectionWithY(y);
  //   point2.setTexturePoint(xText02, yText02);
  //   CanvasLine line = CanvasLine(point1, point2);
  //   line.mapTexture(window, texture);
  // }



  for (int y = v1().y(); y < v2().y(); y++) {
    float ratio12 = (y - v1().y()) / (v2().y() - v1().y());
    float ratio02 = (y - v0().y()) / (v2().y() - v0().y());
    float xText12 = v1().getTexturePoint().x() + ratio12*(v2().getTexturePoint().x() - v1().getTexturePoint().x());
    float yText12 = v1().getTexturePoint().y() + ratio12*(v2().getTexturePoint().y() - v2().getTexturePoint().y());
    float xText02 = v0().getTexturePoint().x() + ratio02*(v2().getTexturePoint().x() - v0().getTexturePoint().x());
    float yText02 = v0().getTexturePoint().y() + ratio02*(v2().getTexturePoint().y() - v0().getTexturePoint().y());
    CanvasPoint point1 = line12.findIntersectionWithY(y);
    point1.setTexturePoint(xText12, yText12);
    CanvasPoint point2 = line02.findIntersectionWithY(y);
    point2.setTexturePoint(xText02, yText02);
    CanvasLine line = CanvasLine(point1, point2);
    line.mapTexture(window, texture);
  }
}

bool vertexComparator(CanvasPoint lhs, CanvasPoint rhs) {
  return lhs.y() < rhs.y();
}

std::ostream &operator<<(std::ostream &os, const CanvasTriangle &triangle) {
	os << triangle._vertices[0] << triangle._vertices[1] << triangle._vertices[2];
	return os;
}
