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
		float _v0Distance;
		float _v1Distance;
		float _v2Distance;

	public:
		RayTriangleIntersection();
		RayTriangleIntersection(const glm::vec3 &point, float distance, float u, float v, const ModelTriangle &triangle);

		bool isNull();
		float getDistanceFromOrigin();
		ModelTriangle getIntersectedTriangle();
		glm::vec3 getIntersectionPoint();
		glm::vec3 getNormal();
		float getV0Distance();
		float getV1Distance();
		float getV2Distance();

		friend std::ostream& operator<<(std::ostream &os, const RayTriangleIntersection &rti);
};
