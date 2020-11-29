#pragma once

#include "CanvasPoint.h"
#include "CanvasLine.h"
#include "Colour.h"
#include "DrawingWindow.h"
#include "Utils.h"

class CanvasTriangle {
	private:
		std::vector<CanvasPoint> _vertices;
		Material _material;

	public:
		CanvasTriangle();
		CanvasTriangle(CanvasPoint v0, CanvasPoint v1, CanvasPoint v2);
		CanvasTriangle(CanvasPoint v0, CanvasPoint v1, CanvasPoint v2, Material _material);

		CanvasPoint &v0();
		CanvasPoint &v1();
		CanvasPoint &v2();

		void drawFrame(DrawingWindow &window);
		void fill(DrawingWindow &window);
		void mapTexture(DrawingWindow &window);
		void orderVertices();
		friend std::ostream &operator<<(std::ostream &os, const CanvasTriangle &triangle);
};

bool vertexComparator(CanvasPoint lhs, CanvasPoint rhs);
