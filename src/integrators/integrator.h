//
// Created by sohaibalam on 02/04/24.
//

#ifndef EPQ_INTEGRATOR_H
#define EPQ_INTEGRATOR_H

#include <Scene.h>
#include <cameras/orthographicCamera.h>
#include <samplers/stratifiedSampler.h>
class integrator {
public:
  ~integrator() {}
  virtual void Render(Scene &scene) = 0;
};

class testIntegrator : public integrator {
public:
  void Render(Scene &scene) override;
  testIntegrator(Scene *scene, stratifiedSampler *sampler,
                 orthographicCamera *camera, uint32_t *data)
      : scene(scene), sampler(sampler), camera(camera), data(data) {}

public:
  Scene *scene;
  stratifiedSampler *sampler;
  orthographicCamera *camera;
  uint32_t *data;
};

#endif // EPQ_INTEGRATOR_H
