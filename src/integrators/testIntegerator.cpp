//
// Created by sohaibalam on 11/04/24.
//

#include "cameras/camera.h"
#include "integrator.h"

#define screenX 800
#define screenY 800

#include <iostream>


void generateRay(CameraSample sample, Ray& ray)
{

}

// this integrator is just for testing purposes, if it hits
// then the pixel is white otherwise black
void testIntegrator::Render(Scene &scene) {
  CameraSample sample{};
  this->scene = const_cast<Scene *>(&scene);
  sampler->Clone(24158789);
  for (int i = 0; i <= screenX; i++) {
    for (int j = 0; j <= screenY; j++) {
      //sampler->StartPixel(glm::vec2(i, j));
      sample.pFilm = glm::vec2(i, j);
      Intersection intersection;
      Ray ray;
      camera->generateRay(sample, &ray);
      if (scene.Intersect(ray, intersection)) {
        data[i * screenX + j] = 0xFFFFFFFF;
      } else {
        data[i * screenX + j] = 0xFF000000;
      }
    }
    std::cout << i << "\n";
  }
}
