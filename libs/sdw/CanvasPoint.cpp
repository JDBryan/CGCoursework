#include "CanvasPoint.h"

//CONSTRUCTORS
CanvasPoint::CanvasPoint() = default;

CanvasPoint::CanvasPoint(glm::vec3 p) {
	_position = p;
	_colour = Colour(0, 0, 0);
}

CanvasPoint::CanvasPoint(glm::vec3 p, Colour c) {
	_position = p;
	_colour = c;
}

CanvasPoint::CanvasPoint(float x, float y, float z) {
	_position = glm::vec3(x, y, z);
	_colour = Colour(0, 0, 0);
}

CanvasPoint::CanvasPoint(float x, float y, float z, Colour c) {
	_position = glm::vec3(x, y, z);
	_colour = c;
}

//GETTERS
float CanvasPoint::x() {
	return _position.x;
}

float CanvasPoint::y() {
	return _position.y;
}

float CanvasPoint::z() {
	return _position.z;
}

//OTHER METHODS
void CanvasPoint::draw(DrawingWindow &window) {
	window.setPixelColour(_position.x, _position.y, _colour);
}

std::ostream &operator<<(std::ostream &os, const CanvasPoint &point) {
	os << "(" << point._position.x << ", " << point._position.y << ", " << point._position.z << ") ";
	return os;
}
