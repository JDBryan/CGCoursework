#include "RayTriangleIntersection.h"

RayTriangleIntersection::RayTriangleIntersection() {
	_isNull = true;
}

RayTriangleIntersection::RayTriangleIntersection(const glm::vec3 &point, float distance, const ModelTriangle &triangle) {
	_intersectionPoint = point;
	_distanceFromCamera = distance;
	_intersectedTriangle = triangle;
	_isNull = false;
}

bool RayTriangleIntersection::isNull() {
	return _isNull;
}

float RayTriangleIntersection::getDistanceFromCamera() {
	return _distanceFromCamera;
}

glm::vec3 RayTriangleIntersection::getIntersectionPoint() {
	return _intersectionPoint;
}

ModelTriangle RayTriangleIntersection::getIntersectedTriangle() {
	return _intersectedTriangle;
}

std::ostream &operator<<(std::ostream &os, const RayTriangleIntersection &rti) {
	if (rti._isNull) {
		os << "Intersection is null";
	} else {
		os << "Intersection is at [" << rti._intersectionPoint[0] << "," << rti._intersectionPoint[1] << "," <<
		rti._intersectionPoint[2] << "] on triangle " << rti._intersectedTriangle <<
		" at a distance of " << rti._distanceFromCamera;
	}
	return os;
}