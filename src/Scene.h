//
// Created by sohaibalam on 03/04/24.
//

#ifndef EPQ_SCENE_H
#define EPQ_SCENE_H

#include <Primitives.h>
#include <memory>
#include <vector>
class Scene {
public:
  Scene() {}
  ~Scene() = default;

  bool Intersect(const Ray &ray, Intersection &intersection);
  void Add(std::shared_ptr<Primitives> primitive);

public:
  std::vector<std::shared_ptr<Primitives>> primitives;
};

#endif // EPQ_SCENE_H
