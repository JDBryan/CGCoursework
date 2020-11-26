#pragma once

#include <iostream>

class TexturePoint {
	private:
		float _x;
		float _y;

	public:
		TexturePoint();
		TexturePoint(float xPos, float yPos);
		float x();
		float y();
		friend std::ostream &operator<<(std::ostream &os, const TexturePoint &point);
};
