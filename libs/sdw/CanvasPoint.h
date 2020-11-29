#pragma once

#include <iostream>
#include "DrawingWindow.h"
#include "Material.h"
#include "TexturePoint.h"
#include <glm/glm.hpp>

class CanvasPoint {
	private:
		glm::vec3 _position;
		Material _material;
		TexturePoint _texturePoint;


	public:
		CanvasPoint();
		CanvasPoint(glm::vec3 p);
		CanvasPoint(glm::vec3 p, Material m);
		CanvasPoint(float x, float y, float z);
		CanvasPoint(float x, float y, float z, Material m);

		float x();
		float y();
		float z();
		TexturePoint getTexturePoint();
		glm::vec3 getPosition();
		glm::vec3 getTextPosition();

		void setTexturePoint(float x, float y);

		void draw(DrawingWindow &window);
		friend std::ostream &operator<<(std::ostream &os, const CanvasPoint &point);
};
