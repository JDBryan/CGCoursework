#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include "ModelTriangle.h"
#include <ostream>
#include <limits>

class RayTriangleIntersection {
	private:
		glm::vec3 _intersectionPoint;
		float _distanceFromOrigin;
		ModelTriangle _intersectedTriangle;
		bool _isNull;

	public:
		RayTriangleIntersection();
		RayTriangleIntersection(const glm::vec3 &point, float distance, const ModelTriangle &triangle);

		bool isNull();
		float getDistanceFromOrigin();
		ModelTriangle getIntersectedTriangle();
		glm::vec3 getIntersectionPoint();

		friend std::ostream& operator<<(std::ostream &os, const RayTriangleIntersection &rti);
};
