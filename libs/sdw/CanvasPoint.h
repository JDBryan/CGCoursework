#pragma once

#include <iostream>
#include "DrawingWindow.h"
#include "Colour.h"
#include <glm/glm.hpp>

class CanvasPoint {
	private:
		glm::vec3 _position;
		Colour _colour;

	public:
		CanvasPoint(float x, float y, float z);
		CanvasPoint(float x, float y, float z, Colour colour);
		void draw(DrawingWindow &window);
		friend std::ostream &operator<<(std::ostream &os, const CanvasPoint &point);

};
