#include "Colour.h"

Colour::Colour() = default;

Colour::Colour(uint32_t colour) {
  _red = (colour >> 16) & 0xff;
  _green = (colour >> 8) & 0xff;
  _blue = colour  & 0xff;
}

Colour::Colour(int r, int g, int b) {
	_red = r;
	_green = g;
	_blue = b;
}

int Colour::red() {
	return _red;
}

int Colour::green() {
	return _green;
}

int Colour::blue() {
	return _blue;
}

uint32_t Colour::pack() {
  return (255 << 24) + (_red << 16) + (_green << 8) + _blue;
}

std::ostream &operator<<(std::ostream &os, const Colour &colour) {
	os << " [" << colour._red << ", " << colour._green << ", " << colour._blue << "]";
	return os;
}
