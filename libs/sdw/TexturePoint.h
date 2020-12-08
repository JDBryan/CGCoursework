#pragma once

#include <iostream>
#include <glm/glm.hpp>

class TexturePoint {
	private:
		float _x;
		float _y;

	public:
		TexturePoint();
		TexturePoint(float xPos, float yPos);
		float x();
		float y();
		glm::vec2 getPosition();
		friend std::ostream &operator<<(std::ostream &os, const TexturePoint &point);
};
