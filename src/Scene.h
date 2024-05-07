//
// Created by sohaibalam on 03/04/24.
//

#ifndef EPQ_SCENE_H
#define EPQ_SCENE_H

#include <memory>
#include <primitives.h>
#include <vector>
class scene {
public:
  scene();
  ~scene();

  bool Intersect(const Ray &ray, Intersection &intersection);
  void Add(std::shared_ptr<primitives> primitive);

public:
  std::vector<std::shared_ptr<primitives>> primitives;
};

#endif // EPQ_SCENE_H
