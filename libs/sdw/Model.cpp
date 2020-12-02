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

void Model::fillRayTracing(DrawingWindow &window, Camera &camera, float scalar) {
  float ratioA = (scalar - 1) / (2 * scalar);
  float ratioB = (scalar + 1) / (2 * scalar);
  for (float x = ratioA*window.width; x < ratioB*window.width; x+= 1/scalar) {
		for (float y = ratioA*window.height; y < ratioB*window.height; y+= 1/scalar) {
			Ray ray = Ray(window, camera, CanvasPoint(x,y,0));
      std::vector<RayTriangleIntersection> intersections;
      for (ModelObject object: getObjects()) {
        for (ModelTriangle triangle: object.getFaces()) {

          intersections.push_back(ray.findTriangleIntersection(triangle, camera));
        }
      }
			RayTriangleIntersection intersection = getClosestIntersection(intersections);

			if (!intersection.isNull()) {
        float scaledX = (x - (window.width/2))*scalar + (window.width/2);
        float scaledY = (y - (window.height/2))*scalar + (window.height/2);
				window.setPixelColour(scaledX, scaledY, 0, intersection.getIntersectedTriangle().getMaterial().getColour());
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
