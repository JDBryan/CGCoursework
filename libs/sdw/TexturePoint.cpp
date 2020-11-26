#include "TexturePoint.h"

TexturePoint::TexturePoint() = default;
TexturePoint::TexturePoint(float xPos, float yPos) {
	_x = xPos;
	_y = yPos;
}

float TexturePoint::x() {
	return _x;
}

float TexturePoint::y() {
	return _y;
}

std::ostream &operator<<(std::ostream &os, const TexturePoint &point) {
	os << "x: " << point._x << " y: " << point._y;
	return os;
}
