//
// Created by sohaibalam on 01/04/24.
//

#ifndef EPQ_ORTHOGRAPHICCAMERA_H
#define EPQ_ORTHOGRAPHICCAMERA_H
#include <cameras/camera.h>

Transform Orthographic(float znear, float zfar) {
  return Scale(1, 1, 1 / (zfar - znear)) * Translate(glm::vec3(0, 0, -znear));
}

class orthographicCamera : projectiveCamera {
public:
  orthographicCamera(const Transform &CameraToWorld,
                     const Bounds2f &screenWindow, float shutterOpe,
                     float shutterClose, float lensRadius, float focalDistance)
      : projectiveCamera(CameraToWorld, Orthographic(0, 1), screenWindow,
                         shutterOpe, shutterClose, lensRadius, focalDistance) {
    dxCamera = RasterToCamera(Vector3f)
  }

public:
  glm::vec3 dxCamera, dyCamera;
};

#endif // EPQ_ORTHOGRAPHICCAMERA_H
