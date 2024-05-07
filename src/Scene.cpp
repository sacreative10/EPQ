//
// Created by sohaibalam on 03/04/24.
//

#include "scene.h"
bool scene::Intersect(const Ray &ray, Intersection &intersection) {

  // do your bvh traversal here
  for (auto &primitive : primitives) {
    Intersection temp{};
    if (primitive->Intersect(ray, temp)) {
      if (temp.t < intersection.t) {
        intersection = temp;
      }
    }
  }
  return false;
}
