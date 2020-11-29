#include <glm/glm.hpp>

class Camera {
  private:
    glm::vec3 _position;
    float _focalLength;

  public:
    Camera(float x, float y, float z, float focalLength);

    float x();
    float y();
    float z();
    glm::vec3 getPosition();
    float getFocalLength();

    void translate(float x, float y, float z);
};
