//
// Created by sohaibalam on 03/04/24.
//

#include "primitives.h"
bool sphere::Intersect(const Ray &ray, Intersection &intersection) {
  glm::vec3 oc = ray.o - center;
  float a = glm::dot(ray.d, ray.d);
  float b = 2.0f * glm::dot(oc, ray.d);
  float c = glm::dot(oc, oc) - radius * radius;
  float discriminant = b * b - 4 * a * c;
  if (discriminant > 0) {
    float temp = (-b - sqrt(discriminant)) / (2.0f * a);
    if (temp < intersection.t) {
      intersection.t = temp;
      intersection.position = ray.o + intersection.t * ray.d;
      intersection.normal = glm::normalize(intersection.position - center);
    }
    return true;
  }
  return false;
}
