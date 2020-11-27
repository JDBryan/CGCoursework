#include "CanvasPoint.h"

//CONSTRUCTORS
CanvasPoint::CanvasPoint() = default;

CanvasPoint::CanvasPoint(glm::vec3 p) {
	_position = p;
	_colour = Colour(0, 0, 0);
	_texturePoint = TexturePoint(-1, -1);
}

CanvasPoint::CanvasPoint(glm::vec3 p, Colour c) {
	_position = p;
	_colour = c;
	_texturePoint = TexturePoint(-1, -1);
}

CanvasPoint::CanvasPoint(float x, float y, float z) {
	_position = glm::vec3(x, y, z);
	_colour = Colour(0, 0, 0);
	_texturePoint = TexturePoint(-1, -1);
}

CanvasPoint::CanvasPoint(float x, float y, float z, Colour c) {
	_position = glm::vec3(x, y, z);
	_colour = c;
	_texturePoint = TexturePoint(-1, -1);
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

glm::vec3 CanvasPoint::getPosition() {
	return _position;
}

glm::vec3 CanvasPoint::getTextPosition() {
	return glm::vec3(_texturePoint.x(), _texturePoint.y(), 0);
}

TexturePoint CanvasPoint::getTexturePoint() {
	return _texturePoint;
}

//SETTERS
void CanvasPoint::setTexturePoint(float x, float y) {
	_texturePoint = TexturePoint(x, y);
}

//OTHER METHODS
void CanvasPoint::draw(DrawingWindow &window) {
	window.setPixelColour(_position.x, _position.y, _colour);
}

std::ostream &operator<<(std::ostream &os, const CanvasPoint &point) {
	os << "(" << point._position.x << ", " << point._position.y << ", " << point._position.z << ") ";
	return os;
}
