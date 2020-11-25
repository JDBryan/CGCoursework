#pragma once

#include "CanvasPoint.h"
#include "CanvasLine.h"
#include "Colour.h"
#include "DrawingWindow.h"

class CanvasTriangle {
	private:
		std::vector<CanvasPoint> _vertices{};
		Colour _colour;

	public:
		CanvasTriangle();
		CanvasTriangle(CanvasPoint v0, CanvasPoint v1, CanvasPoint v2);
		CanvasTriangle(CanvasPoint v0, CanvasPoint v1, CanvasPoint v2, Colour colour);

		CanvasPoint &v0();
		CanvasPoint &v1();
		CanvasPoint &v2();

		void drawFrame(DrawingWindow &window);
		bool vertexComparator(CanvasPoint lhs, CanvasPoint rhs);
		void orderVertices();
		friend std::ostream &operator<<(std::ostream &os, const CanvasTriangle &triangle);
};
