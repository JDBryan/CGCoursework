#include "Colour.h"

Colour::Colour(int r, int g, int b) {
	_red = r;
	_green = g;
	_blue = b;
}

std::ostream &operator<<(std::ostream &os, const Colour &colour) {
	os << " [" << colour._red << ", " << colour._green << ", " << colour._blue << "]";
	return os;
}

uint32_t Colour::pack() {
  return (255 << 24) + (_red << 16) + (_green << 8) + _blue;
}
