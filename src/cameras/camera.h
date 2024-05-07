//
// Created by sohaibalam on 01/04/24.
//

#ifndef EPQ_CAMERA_H
#define EPQ_CAMERA_H

#include <geometry.h>

struct CameraSample {
  glm::vec2 pFilm;
  glm::vec2 pLens;
  float time;
};

class camera {
public:
  camera(const Transform &CameraToWorld, float shutterOpen, float shutterClose)
      : CameraToWorld(CameraToWorld), shutterOpen(shutterOpen),
        shutterClose(shutterClose) {}

  virtual float generateRay(const CameraSample &sample, Ray *ray) const = 0;

  virtual float generateRayDifferential(const CameraSample &sample,
                                        RayDifferential *rd) const;

public:
  Transform CameraToWorld;
  const float shutterOpen, shutterClose;

  ~camera() = default;
};

class projectiveCamera : public camera {
public:
  projectiveCamera(const Transform &CameraToWorld,
                   const Transform &CameraToScreen,
                   const Bounds2f &screenWindow, float shutterOpen,
                   float shutterClose, float lensr, float focald)
      : camera(CameraToWorld, shutterOpen, shutterClose),
        CameraToScreen(CameraToScreen) {
    ScreenToRaster =
        Scale(screenWindow.pMax.x - screenWindow.pMin.x,
              screenWindow.pMax.y - screenWindow.pMin.y, 1) *
        Translate(glm::vec3(1 / (screenWindow.pMax.x - screenWindow.pMin.x),
                            1 / (screenWindow.pMin.y - screenWindow.pMax.y),
                            1)) *
        Translate(glm::vec3(-screenWindow.pMin.x, -screenWindow.pMin.y, 0));
    RasterToScreen = Inverse(ScreenToRaster);
    RasterToCamera = Inverse(CameraToScreen) * RasterToScreen;
    lensRadius = lensr;
    focalDistance = focald;
  }

public:
  Transform CameraToScreen, RasterToCamera;
  Transform ScreenToRaster, RasterToScreen;
  float lensRadius, focalDistance;
};

#endif // EPQ_CAMERA_H
