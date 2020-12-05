#include "Model.h"

Model::Model(std::string fileLocation, std::string fileName, float scalar) {
  std::map<std::string, Material> materials;
  std::vector<ModelPoint> vertices;
  std::vector<TexturePoint> texturePoints;

  std::ifstream infile(fileLocation + fileName);
  std::string line;
  bool currentObjectIsNull = true;
  ModelObject currentObject;

  while (std::getline(infile, line)) {
    std::vector<std::string> tokens = split(line, ' ');
    if (tokens[0] == "mtllib") {
      materials = loadMaterials(fileLocation, tokens[1]);

    } else if (tokens[0] == "o") {
      if (!currentObjectIsNull) {
        _objects.push_back(currentObject);
      }
      currentObject = ModelObject(tokens[1]);
      currentObjectIsNull = false;

    } else if (tokens[0] == "usemtl") {
      currentObject.setMaterial(materials[tokens[1]]);

    } else if (tokens[0] == "v") {
      ModelPoint vertex = ModelPoint(std::stof(tokens[1])*scalar, std::stof(tokens[2])*scalar, std::stof(tokens[3])*scalar);
      vertices.push_back(vertex);

    } else if (tokens[0] == "vt") {
      TexturePoint texturePoint = TexturePoint(std::stof(tokens[1])*480, std::stof(tokens[2])*395);
      texturePoints.push_back(texturePoint);

    } else if (tokens[0] == "f") {
      std::vector<std::string> indicesA = split(tokens[1], '/');
      std::vector<std::string> indicesB = split(tokens[2], '/');
      std::vector<std::string> indicesC = split(tokens[3], '/');
      ModelPoint v0 = vertices[std::stoi(indicesA[0])-1];
      ModelPoint v1 = vertices[std::stoi(indicesB[0])-1];
      ModelPoint v2 = vertices[std::stoi(indicesC[0])-1];
      if (indicesA[1] != "") {
        v0.setTexturePoint(texturePoints[std::stoi(indicesA[1])-1]);
        v1.setTexturePoint(texturePoints[std::stoi(indicesB[1])-1]);
        v2.setTexturePoint(texturePoints[std::stoi(indicesC[1])-1]);
      }
      currentObject.addFace(v0, v1, v2);
    }
  }
  if (!currentObjectIsNull){
      _objects.push_back(currentObject);
  }
}

std::map<std::string, Material> Model::loadMaterials(std::string fileLocation, std::string fileName) {
  std::ifstream infile(fileLocation + fileName);
  std::string line;

  std::map<std::string, Material> materials;
  bool currentMaterialIsNull = true;
  Material currentMaterial;

  while (std::getline(infile, line)) {
    std::vector<std::string> tokens = split(line, ' ');

    if (tokens[0] == "newmtl") {
      if (!currentMaterialIsNull) {
        materials[currentMaterial.getName()] = currentMaterial;
      }
      currentMaterial = Material(tokens[1]);
      currentMaterialIsNull = false;

    } else if (tokens[0] == "Kd") {
      Colour colour = Colour(std::stof(tokens[1])*255, std::stof(tokens[2])*255, std::stof(tokens[3])*255);
      currentMaterial.setColour(colour);

    } else if (tokens[0] == "map_Kd"){
      TextureMap texture = TextureMap(fileLocation + tokens[1]);
      currentMaterial.setTexture(texture);
    }
  }

  if (!currentMaterialIsNull) {
    materials[currentMaterial.getName()] = currentMaterial;
  }

  return materials;
}

std::vector<ModelObject> Model::getObjects() {
  return _objects;
}

void Model::drawFrame(DrawingWindow &window, Camera &camera, float scalar) {
  for (ModelObject object: _objects) {
    object.drawFrame(window, camera, scalar);
  }
}

void Model::fill(DrawingWindow &window, Camera &camera, float scalar) {
  for (ModelObject object: _objects) {
    object.fill(window, camera, scalar);
  }
}

void Model::fillRayTracing(DrawingWindow &window, Camera &camera, float scalar, std::string lighting) {
  glm::vec3 light = glm::vec3(0,0,1);
  float startRatio = (scalar - 1) / (2 * scalar);
  float endRatio = (scalar + 1) / (2 * scalar);

  std::vector<ModelTriangle> faces;
  for (ModelObject object: _objects) {
    for (ModelTriangle triangle: object.getFaces()) {
      std::cout << object.getName() << std::endl;
      std::cout << glm::to_string(triangle.getNormal()) << std::endl;
      faces.push_back(triangle);
    }
  }

  for (float x = startRatio*window.width; x <= endRatio*window.width; x+= 1/(scalar+1)) {
		for (float y = startRatio*window.height; y <= endRatio*window.height; y+= 1/(scalar+1)) {

			Ray ray = Ray(window, camera, CanvasPoint(x,y,0));
			RayTriangleIntersection intersection = getClosestIntersection(ray, faces);

			if (!intersection.isNull()) {
        Ray lightRay = Ray(light, intersection.getIntersectionPoint());
  			RayTriangleIntersection lightIntersection = getClosestIntersection(lightRay, faces);

        float scaledX = (x - (window.width/2))*scalar + (window.width/2);
        float scaledY = (y - (window.height/2))*scalar + (window.height/2);

        float brightness;
        glm::vec3 normal = intersection.getIntersectedTriangle().getNormal();
        Material material = intersection.getIntersectedTriangle().getMaterial();
        if(!lightIntersection.isNull() && 0.0001 <= glm::length(lightIntersection.getIntersectionPoint()-intersection.getIntersectionPoint())) {
          brightness = 0;
        } else {
          if (lighting == "proximity") {
            float r =  glm::length(light - lightIntersection.getIntersectionPoint());
            brightness = 1 / (4 * M_PI * r * r);

          } else if (lighting == "angle of incidence") {
            float angleOfIncidence = glm::dot(normal, -lightRay.getDirection());
            brightness = angleOfIncidence;

          } else if (lighting == "specular") {
            glm::vec3 ri = glm::normalize(lightRay.getDirection());
            glm::vec3 rr = glm::normalize(ri - normal * (float)(2*glm::dot(ri, normal)));
            brightness = pow(glm::dot(-ray.getDirection(), rr), 64);

          } else if (lighting == "all") {
            float r =  glm::length(light - lightIntersection.getIntersectionPoint());
            float brightness1 = 1 / (4 * M_PI * r * r);

            glm::vec3 normal = intersection.getIntersectedTriangle().getNormal();
            float angleOfIncidence = glm::dot(normal, -lightRay.getDirection());
            float brightness2 = angleOfIncidence;

            glm::vec3 ri = glm::normalize(lightRay.getDirection());
            glm::vec3 rr = glm::normalize(ri - normal * (float)(2*glm::dot(ri, normal)));
            float brightness3 = 3*pow(glm::dot(-ray.getDirection(), rr), 64);

            brightness = (brightness1 + brightness2 + brightness3)/3;

          } else {
            brightness = 1;
          }
        }
        brightness += 0.2;
        material.setBrightness(brightness);
        window.hardSetPixelColour(scaledX, scaledY, 0, material.getColour());
			}
		}
  }
  std::cout << "done" << std::endl;
}

void Model::fillWithTextures(DrawingWindow &window, Camera &camera, float scalar) {
  for (ModelObject object: _objects) {
    if (object.getMaterial().hasTexture()) {
      object.mapTexture(window, camera, scalar);
    } else {
      object.fill(window, camera, scalar);
    }
  }
}

RayTriangleIntersection getClosestIntersection(Ray ray, std::vector<ModelTriangle> faces) {
  std::vector<RayTriangleIntersection> intersections;
  for (ModelTriangle triangle: faces) {
    intersections.push_back(ray.findTriangleIntersection(triangle));
  }
  RayTriangleIntersection closestIntersection;
  float currentShortestDistance = std::numeric_limits<float>::infinity();
  for (RayTriangleIntersection intersection: intersections) {
    if (intersection.getDistanceFromOrigin() < currentShortestDistance && intersection.getDistanceFromOrigin() > 0) {
      currentShortestDistance = intersection.getDistanceFromOrigin();
      closestIntersection = intersection;
    }
  }
  return closestIntersection;
}
