#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include "ModelTriangle.h"
#include <ostream>

class RayTriangleIntersection {
	private:
		glm::vec3 _intersectionPoint;
		float _distanceFromCamera;
		ModelTriangle _intersectedTriangle;
		bool _isNull;

	public:
		RayTriangleIntersection();
		RayTriangleIntersection(const glm::vec3 &point, float distance, const ModelTriangle &triangle);

		bool isNull();
		float getDistanceFromCamera();
		ModelTriangle getIntersectedTriangle();
		glm::vec3 getIntersectionPoint();

		friend std::ostream& operator<<(std::ostream &os, const RayTriangleIntersection &rti);
};
