//
// Created by sohaibalam on 01/04/24.
//

#ifndef EPQ_ORTHOGRAPHICCAMERA_H
#define EPQ_ORTHOGRAPHICCAMERA_H
#include <cameras/camera.h>
#include <geometry.h>

Transform Orthographic(float znear, float zfar) {
  return Scale(1, 1, 1 / (zfar - znear)) * Translate(glm::vec3(0, 0, -znear));
}

// TODO: Implement lensRadius and focalDistance for orthographicCamera

class orthographicCamera : projectiveCamera {
public:
  orthographicCamera(const Transform &CameraToWorld,
                     const Bounds2f &screenWindow, float shutterOpe,
                     float shutterClose, float lensRadius, float focalDistance)
      : projectiveCamera(CameraToWorld, Orthographic(0, 1), screenWindow,
                         shutterOpe, shutterClose, lensRadius, focalDistance) {
    dxCamera = RasterToCamera(glm::vec3(1, 0, 0));
    dyCamera = RasterToCamera(glm::vec3(0, 1, 0));
  }
  float GenerateRay(const CameraSample &sample, Ray *ray) const {
    glm::vec3 pFilm = glm::vec3(sample.pFilm.x, sample.pFilm.y, 0);
    glm::vec3 pCamera = RasterToCamera(pFilm);
    *ray = Ray(pCamera, glm::vec3(0, 0, 1), 0, INFINITY);
    ray->time = Lerp(sample.time, shutterOpen, shutterClose);
    *ray = CameraToWorld(*ray);
    return 1;
  }

  float GenerateRayDifferential(const CameraSample &sample,
                                RayDifferential *rd) const {
    glm::vec3 pFilm = glm::vec3(sample.pFilm.x, sample.pFilm.y, 0);
    glm::vec3 pCamera = RasterToCamera(pFilm);
    *rd = RayDifferential(pCamera, glm::vec3(0, 0, 1), 0, INFINITY);

    rd->time = Lerp(sample.time, shutterOpen, shutterClose);
    *rd = CameraToWorld(*rd);
    rd->rxOrigin = rd->o + dxCamera;
    return 1;
  }

public:
  glm::vec3 dxCamera, dyCamera;
};

#endif // EPQ_ORTHOGRAPHICCAMERA_H
