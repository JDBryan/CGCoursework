#include <glm/glm.hpp>

class Camera {
  private:
    glm::vec3 _position;
    glm::mat3 _orientation;
    float _focalLength;

  public:
    Camera(float x, float y, float z, float focalLength);

    float x();
    float y();
    float z();
    glm::vec3 getPosition();
    glm::mat3 getOrientation();
    float getFocalLength();

    void translate(float x, float y, float z);
    void tilt(float angle);
    void pan(float angle);
    void roll(float angle);
    void orbitX(float angle);
};
