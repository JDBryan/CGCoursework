#include "CanvasPoint.h"

CanvasPoint::CanvasPoint(float x, float y, float z) {
	_position = glm::vec3(x, y, z);
	_colour = Colour(0, 0, 0);
}


CanvasPoint::CanvasPoint(float x, float y, float z, Colour c) {
	_position = glm::vec3(x, y, z);
	_colour = c;
}

void CanvasPoint::draw(DrawingWindow &window) {
	window.setPixelColour(_position.x, _position.y, _colour);
}

std::ostream &operator<<(std::ostream &os, const CanvasPoint &point) {
	os << "(" << point._position.x << ", " << point._position.y << ", " << point._position.z << ") ";
	return os;
}
