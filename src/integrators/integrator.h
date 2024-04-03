//
// Created by sohaibalam on 02/04/24.
//

#ifndef EPQ_INTEGRATOR_H
#define EPQ_INTEGRATOR_H

class Scene;

class integrator {
public:
  virtual ~integrator();
  virtual void Render(const Scene &scene) = 0;
};

class SamplerIntegrator : public integrator {};

#endif // EPQ_INTEGRATOR_H
