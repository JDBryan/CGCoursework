#include "RayTriangleIntersection.h"

RayTriangleIntersection::RayTriangleIntersection() {
	_isNull = true;
	_distanceFromOrigin = std::numeric_limits<float>::infinity();
}

RayTriangleIntersection::RayTriangleIntersection(const glm::vec3 &point, float distance, float u, float v, const ModelTriangle &triangle) {
	_v1Distance = u;
	_v2Distance = v;
	_v0Distance = 1.0f - (_v1Distance + _v2Distance);
	_intersectionPoint = point;
	_distanceFromOrigin = distance;
	_intersectedTriangle = triangle;
	_isNull = false;
}

bool RayTriangleIntersection::isNull() {
	return _isNull;
}

float RayTriangleIntersection::getDistanceFromOrigin() {
	return _distanceFromOrigin;
}

glm::vec3 RayTriangleIntersection::getIntersectionPoint() {
	return _intersectionPoint;
}

ModelTriangle RayTriangleIntersection::getIntersectedTriangle() {
	return _intersectedTriangle;
}

glm::vec3 RayTriangleIntersection::getNormal() {
	if (_intersectedTriangle.v0().hasNormal() && _intersectedTriangle.v1().hasNormal() && _intersectedTriangle.v2().hasNormal()) {
		glm::vec3 v0Norm = _intersectedTriangle.v0().getNormal();
		glm::vec3 v1Norm = _intersectedTriangle.v1().getNormal();
		glm::vec3 v2Norm = _intersectedTriangle.v2().getNormal();
		glm::vec3 normal = v0Norm * _v0Distance + v1Norm * _v1Distance + v2Norm * _v2Distance;
		return glm::normalize(normal);

	} else {
		return _intersectedTriangle.getNormal();
	}
}

std::ostream &operator<<(std::ostream &os, const RayTriangleIntersection &rti) {
	if (rti._isNull) {
		os << "Intersection is null";
	} else {
		os << "Intersection is at [" << rti._intersectionPoint[0] << "," << rti._intersectionPoint[1] << "," <<
		rti._intersectionPoint[2] << "] on triangle " << rti._intersectedTriangle <<
		" at a distance of " << rti._distanceFromOrigin;
	}
	return os;
}
