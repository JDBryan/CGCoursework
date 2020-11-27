#pragma once

#include <iostream>
//#include <utility>

class Colour {
	private:
		int _red;
		int _green;
		int _blue;

	public:
		Colour();
		Colour(uint32_t c);
		Colour(int r, int g, int b);

		int red();
		int green();
		int blue();
		
		uint32_t pack();
		friend std::ostream &operator<<(std::ostream &os, const Colour &colour);
};
