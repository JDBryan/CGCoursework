#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <utility>
#include "Colour.h"
#include "ModelPoint.h"
#include "CanvasTriangle.h"

class ModelTriangle {

	private:
		std::vector<ModelPoint> _vertices;
		glm::vec3 _normal;
		Material _material;

	public:
		ModelTriangle();
		ModelTriangle(ModelPoint v0, ModelPoint v1, ModelPoint v2);
		ModelTriangle(ModelPoint v0, ModelPoint v1, ModelPoint v2, Material m);

		ModelPoint v0();
		ModelPoint v1();
		ModelPoint v2();
		Material getMaterial();
		glm::vec3 getNormal();

		CanvasTriangle project(DrawingWindow &window, Camera &camera, float scalar);
		void drawFrame(DrawingWindow &window, Camera &camera, float scalar);
		void fill(DrawingWindow &window, Camera &camera, float scalar);
		void mapTexture(DrawingWindow &window, Camera &camera, float scalar);
		friend std::ostream &operator<<(std::ostream &os, ModelTriangle triangle);


};
