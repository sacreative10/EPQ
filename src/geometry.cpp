//
// Created by sohaibalam on 01/04/24.
//

#include "geometry.h"
#include <glm/gtc/matrix_transform.hpp>
// we will use glm's own functions to create the transformations

Transform Translate(const glm::vec3 &delta) {
  glm::mat4 m = glm::translate(glm::mat4(1.0f), delta);
  return Transform(m, glm::inverse(m));
}

Transform Scale(float x, float y, float z) {
  glm::mat4 m = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
  return Transform(m, glm::inverse(m));
}

Transform Rotate(float theta, const glm::vec3 &axis) {
  glm::mat4 m = glm::rotate(glm::mat4(1.0f), glm::radians(theta), axis);
  return Transform(m, glm::inverse(m));
}

Transform LookAt(const glm::vec3 &pos, const glm::vec3 &look,
                 const glm::vec3 &up) {
  glm::mat4 m = glm::lookAt(pos, look, up);
  return Transform(m, glm::inverse(m));
}

glm::vec3 Transform::operator()(const glm::vec3 &v) const {
  return glm::vec4(v, 1) * m;
}

Ray Transform::operator()(const Ray &r) const {
  glm::vec3 oError = r.o;
  glm::vec3 o = glm::vec4(r.o, 1) * m;
  glm::vec3 d = glm::vec4(r.d, 0) * m;
  return Ray(o, d, r.tMax, r.time);
}

float Lerp(float t, float v1, float v2) { return (1 - t) * v1 + t * v2; }