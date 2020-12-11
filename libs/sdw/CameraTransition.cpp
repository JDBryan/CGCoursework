#include "CameraTransition.h"

CameraTransition::CameraTransition(CameraWayPoint start, CameraWayPoint end, int frames) {
  _currentFrame = 0;
  _frames = frames;
  _lookAts = interpolateVectors(start.getLookAt(), end.getLookAt(), frames);
  _positions = interpolateVectors(start.position(), end.position(), frames);
}

bool CameraTransition::doStep(Camera &camera) {
  camera.setPosition(_positions[_currentFrame]);
  camera.lookAt(_lookAts[_currentFrame]);
  _currentFrame++;
  if (_currentFrame == _frames+1) {
    return false;
  } else {
    return true;
  }
}
