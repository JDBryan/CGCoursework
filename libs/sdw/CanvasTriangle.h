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
		CanvasPoint getFurthestPointFromCamera();
		CanvasPoint getClosestPointFromCamera();

		void drawFrame(DrawingWindow &window);
		void fill(DrawingWindow &window);
		void mapTexture(DrawingWindow &window);
		void orderVerticesByHeight();
		void orderVerticesByDepth();
		void orderVerticesByWidth();
		friend std::ostream &operator<<(std::ostream &os, const CanvasTriangle &triangle);
};

bool vertexYComparator(CanvasPoint lhs, CanvasPoint rhs);
bool vertexZComparator(CanvasPoint lhs, CanvasPoint rhs);
bool vertexXComparator(CanvasPoint lhs, CanvasPoint rhs);
