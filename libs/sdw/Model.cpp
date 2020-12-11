#include "Model.h"

Model::Model(std::string fileLocation, std::string fileName, float scalar) {
  std::map<std::string, Material> materials;
  std::vector<ModelPoint> vertices;
  std::vector<glm::vec3> normals;
  std::vector<TexturePoint> texturePoints;

  std::ifstream infile(fileLocation + fileName);
  std::string line;
  bool currentObjectIsNull = true;
  ModelObject currentObject = ModelObject();

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

    } else if (tokens[0] == "vn") {
      glm::vec3 normal = glm::vec3(std::stof(tokens[1])*scalar, std::stof(tokens[2])*scalar, std::stof(tokens[3])*scalar);
      normals.push_back(normal);

    } else if (tokens[0] == "vt") {
      TexturePoint texturePoint = TexturePoint(std::stof(tokens[1])*currentObject.getMaterial().getTexture().width, std::stof(tokens[2])*currentObject.getMaterial().getTexture().height);
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
      if (indicesA.size() > 2 && indicesA[2] != "") {
        v0.setNormal(normals[std::stoi(indicesA[2])-1]);
        v1.setNormal(normals[std::stoi(indicesB[2])-1]);
        v2.setNormal(normals[std::stoi(indicesC[2])-1]);
      }
      currentObject.addFace(v0, v1, v2);
    }
  }
  _objects.push_back(currentObject);
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
      if (tokens[1] == "Blue") {
        currentMaterial.setReflectivity(1);
      }
      currentMaterialIsNull = false;

    } else if (tokens[0] == "Kd") {
      Colour colour = Colour(std::stof(tokens[1])*255, std::stof(tokens[2])*255, std::stof(tokens[3])*255);
      currentMaterial.setColour(colour);

    } else if (tokens[0] == "map_Kd"){
      std::cout << tokens[1] << std::endl;
      TextureMap texture = TextureMap(fileLocation + tokens[1]);
      currentMaterial.setTexture(texture);
    }
  }

  if (!currentMaterialIsNull) {
    materials[currentMaterial.getName()] = currentMaterial;
  }

  return materials;
}

void Model::merge(Model secondModel) {
  for (ModelObject object: secondModel.getObjects()) {
    _objects.push_back(object);
  }
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

void Model::fillRayTracing(DrawingWindow &window, Camera &camera, float scalar, std::string lightingType, std::string shading) {
  Light light = Light(glm::vec3(0,0,1), 0.025);
  float startRatio = (scalar - 1) / (2 * scalar);
  float endRatio = (scalar + 1) / (2 * scalar);

  std::vector<ModelTriangle> faces;
  for (ModelObject object: _objects) {
    for (ModelTriangle triangle: object.getFaces()) {
      faces.push_back(triangle);
    }
  }

  float counter = 1;
  int percent = 1;
  for (float x = startRatio*window.width; x <= endRatio*window.width; x+= 1/(scalar+1)) {
		for (float y = startRatio*window.height; y <= endRatio*window.height; y+= 1/(scalar+1)) {
      counter ++;
      if ((counter/(window.width*window.height))*100 > percent) {
        std::cout << (int)(counter/(window.width*window.height)*100) << std::endl;
        percent += 1;
      }
			Ray cameraRay = Ray(window, camera, CanvasPoint(x,y,0));
			RayTriangleIntersection cameraRayIntersection = getClosestIntersection(cameraRay, faces);
      Material material = cameraRayIntersection.getIntersectedTriangle().getMaterial();

      if (!cameraRayIntersection.isNull() && material.getReflectivity() == 1) {
        Ray reflectedCameraRay = cameraRay.reflect(cameraRayIntersection);
        cameraRayIntersection = getClosestIntersection(reflectedCameraRay, faces);
        cameraRay = reflectedCameraRay;
      }

      material = cameraRayIntersection.getIntersectedTriangle().getMaterial();

			if (!cameraRayIntersection.isNull()) {
        glm::vec3 normal;
        if (shading == "phong") {
          normal = cameraRayIntersection.getNormal();
        } else {
          normal = cameraRayIntersection.getIntersectedTriangle().getNormal();
        }

        float brightness;
        if (shading == "gouraud") {
          glm::vec3 v0norm = cameraRayIntersection.getIntersectedTriangle().v0().getNormal();
      		glm::vec3 v1norm = cameraRayIntersection.getIntersectedTriangle().v1().getNormal();
      		glm::vec3 v2norm = cameraRayIntersection.getIntersectedTriangle().v2().getNormal();
          float v0distance = cameraRayIntersection.getV0Distance();
          float v1distance = cameraRayIntersection.getV1Distance();
          float v2distance = cameraRayIntersection.getV2Distance();
          float v0brightness = getBrightness(faces, cameraRay, cameraRayIntersection, light, v0norm, lightingType);
          float v1brightness = getBrightness(faces, cameraRay, cameraRayIntersection, light, v1norm, lightingType);
          float v2brightness = getBrightness(faces, cameraRay, cameraRayIntersection, light, v2norm, lightingType);

      		brightness = v0brightness * v0distance + v1brightness * v1distance + v2brightness * v2distance;
        } else {
          brightness = getBrightness(faces, cameraRay, cameraRayIntersection, light, normal, lightingType);
          //brightness = 1;
        }
        material.setBrightness(brightness);

        float scaledX = (x - (window.width/2))*scalar + (window.width/2);
        float scaledY = (y - (window.height/2))*scalar + (window.height/2);
        window.hardSetPixelColour(scaledX, scaledY, 0, material.getColour());
			}
		}
  }
  std::cout << "done" << std::endl;
}

float Model::getBrightness(std::vector<ModelTriangle> faces, Ray cameraRay, RayTriangleIntersection cameraRayIntersection, Light light, glm::vec3 normal, std::string lightingType) {
  Ray lightRay = Ray(light.getPoint(), cameraRayIntersection.getIntersectionPoint());
  float brightness;
  float numberOfRaysHitting = 0;
  std::vector<glm::vec3> lightPoints  = light.getAllPoints(2);

  for (glm::vec3 point: lightPoints) {
    Ray ray = Ray(point, cameraRayIntersection.getIntersectionPoint());
    if(!doesIntersect(ray, faces, glm::length(point - cameraRayIntersection.getIntersectionPoint()))) {
      numberOfRaysHitting++;
    }
  }

  float shadowFactor = numberOfRaysHitting/lightPoints.size();

  if (lightingType == "proximity") {
    glm::vec3 distanceToLight = light.getPoint() - cameraRayIntersection.getIntersectionPoint();
    float r =  glm::dot(distanceToLight, distanceToLight);
    brightness = 1 / (4 * M_PI * r * r);

  } else if (lightingType == "angle of incidence") {
    float angleOfIncidence = glm::dot(normal, -lightRay.getDirection());
    brightness = angleOfIncidence;

  } else if (lightingType == "specular") {
    Ray reflectedRay = lightRay.reflect(cameraRayIntersection);
    brightness = pow(glm::dot(-cameraRay.getDirection(), reflectedRay.getDirection()), 64);

  } else if (lightingType == "all") {
    glm::vec3 distanceToLight = light.getPoint() - cameraRayIntersection.getIntersectionPoint();
    float r =  glm::dot(distanceToLight, distanceToLight);
    float brightness1 = 1 / (4 * M_PI * r * r);

    float angleOfIncidence = glm::dot(normal, -lightRay.getDirection());
    float brightness2 = angleOfIncidence;

    Ray reflectedRay = lightRay.reflect(cameraRayIntersection);
    float brightness3 = pow(glm::dot(-cameraRay.getDirection(), reflectedRay.getDirection()), 64);

    brightness = (brightness1 + brightness2 + brightness3)/3;

  } else {
    brightness = 1;
  }

  brightness += 0.2;
  return brightness*shadowFactor;
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

RayTriangleIntersection Model::getClosestIntersection(Ray ray, std::vector<ModelTriangle> faces) {
  RayTriangleIntersection closestIntersection;
  float currentShortestDistance = std::numeric_limits<float>::infinity();
  for (ModelTriangle triangle: faces) {

    glm::vec3 e0 = triangle.v1().getPosition() - triangle.v0().getPosition();
    glm::vec3 e1 = triangle.v2().getPosition() - triangle.v0().getPosition();
    glm::vec3 SPVector = ray.getPosition() - triangle.v0().getPosition();
    glm::mat3 DEMatrix(-ray.getDirection(), e0, e1);
    glm::vec3 possibleSolution = glm::inverse(DEMatrix) * SPVector;

    if (possibleSolution[1] <= 1 && possibleSolution[1] >= 0 && possibleSolution[2] <= 1 && possibleSolution[2] >= 0 && possibleSolution[1] + possibleSolution[2] <= 1) {
      if (possibleSolution[0] < currentShortestDistance && possibleSolution[0] > 0) {
        glm::vec3 r = triangle.v0().getPosition() + (possibleSolution[1] * e0) + (possibleSolution[2] * e1);
        closestIntersection = RayTriangleIntersection(r, possibleSolution[0], possibleSolution[1], possibleSolution[2], triangle);
        currentShortestDistance = possibleSolution[0];
      }
    }
  }
  return closestIntersection;
}

bool Model::doesIntersect(Ray ray, std::vector<ModelTriangle> faces, float rayLength) {
  for (ModelTriangle triangle: faces) {

    glm::vec3 e0 = triangle.v1().getPosition() - triangle.v0().getPosition();
    glm::vec3 e1 = triangle.v2().getPosition() - triangle.v0().getPosition();
    glm::vec3 SPVector = ray.getPosition() - triangle.v0().getPosition();
    glm::mat3 DEMatrix(-ray.getDirection(), e0, e1);
    glm::vec3 possibleSolution = glm::inverse(DEMatrix) * SPVector;

    if (possibleSolution[1] <= 1 && possibleSolution[1] >= 0 && possibleSolution[2] <= 1 && possibleSolution[2] >= 0 && possibleSolution[1] + possibleSolution[2] <= 1) {
      if (possibleSolution[0] < rayLength - 0.0001 && possibleSolution[0] > 0) {
        return true;
      }
    }
  }
  return false;
}
