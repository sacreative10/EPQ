//
// Created by sohaibalam on 03/04/24.
//

#ifndef EPQ_PRIMITIVES_H
#define EPQ_PRIMITIVES_H

#include <geometry.h>

struct Intersection {
  glm::vec3 position;
  glm::vec3 normal;
  float t;
};

class primitives {
public:
  primitives();
  virtual bool Intersect(const Ray &ray, Intersection &intersection) = 0;

  ~primitives();

private:
};

class sphere : public primitives {
public:
  sphere(const glm::vec3 &center, float radius)
      : center(center), radius(radius) {}

  bool Intersect(const Ray &ray, Intersection &intersection) override;

private:
  glm::vec3 center;
  float radius;
};

#endif // EPQ_PRIMITIVES_H
