#pragma once
#include "CanvasPoint.h"
#include "Colour.h"
#include "Utils.h"
#include "DrawingWindow.h"
#include "TextureMap.h"

class CanvasLine {
	private:
		CanvasPoint _v0;
		CanvasPoint _v1;
		Material _material;

	public:
		CanvasLine();
		CanvasLine(CanvasPoint v0, CanvasPoint v1);
		CanvasLine(CanvasPoint v0, CanvasPoint v1, Material m);

		CanvasPoint v0();
		CanvasPoint v1();

		void draw(DrawingWindow &window);
		void mapTexture(DrawingWindow &window);
		CanvasPoint findIntersectionWithY(float y);
		float length();

		friend std::ostream &operator<<(std::ostream &os, const CanvasLine &line);

};
