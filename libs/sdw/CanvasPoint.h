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
		CanvasPoint();
		CanvasPoint(glm::vec3 p);
		CanvasPoint(glm::vec3 p, Colour c);
		CanvasPoint(float x, float y, float z);
		CanvasPoint(float x, float y, float z, Colour c);

		float x();
		float y();
		float z();
		
		void draw(DrawingWindow &window);
		friend std::ostream &operator<<(std::ostream &os, const CanvasPoint &point);
};
