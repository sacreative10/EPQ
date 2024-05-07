//
// Created by sohaibalam on 01/04/24.
//

#ifndef EPQ_GEOMETRY_H
#define EPQ_GEOMETRY_H

#include <glm/glm.hpp>

class Bounds2f {
public:
  Bounds2f() {
    pMin = glm::vec2(INFINITY, INFINITY);
    pMax = glm::vec2(-INFINITY, -INFINITY);
  }

  Bounds2f(const glm::vec2 &p) : pMin(p), pMax(p) {}

  Bounds2f(const glm::vec2 &p1, const glm::vec2 &p2) {
    pMin = glm::vec2(glm::min(p1.x, p2.x), glm::min(p1.y, p2.y));
    pMax = glm::vec2(glm::max(p1.x, p2.x), glm::max(p1.y, p2.y));
  }

  glm::vec2 Diagonal() const { return pMax - pMin; }

  float Area() const {
    glm::vec2 d = Diagonal();
    return d.x * d.y;
  }

  glm::vec2 pMin, pMax;
};

class Ray {
public:
  Ray() {}

  Ray(const glm::vec3 &o, const glm::vec3 &d, float tMax = INFINITY,
      float time = 0.0f)
      : o(o), d(d), tMax(tMax), time(time) {}

  glm::vec3 operator()(float t) const { return o + d * t; }

public:
  glm::vec3 o;
  glm::vec3 d;
  mutable float tMax;
  float time; // unused
};

class RayDifferential : public Ray {
public:
  RayDifferential() {}

  RayDifferential(const glm::vec3 &o, const glm::vec3 &d, float tMax = INFINITY,
                  float time = 0.0f)
      : Ray(o, d, tMax, time) {}

  RayDifferential(const Ray &ray) : Ray(ray) {}

  glm::vec3 rxOrigin, ryOrigin;
  glm::vec3 rxDirection, ryDirection;
  bool hasDifferentials;
};

class Transform {
public:
  Transform() {}

  Transform(const glm::mat4 &m) : m(m), mInv(glm::inverse(m)) {}

  Transform(const glm::mat4 &m, const glm::mat4 &mInv) : m(m), mInv(mInv) {}

  friend Transform Inverse(const Transform &t) {
    return Transform(t.mInv, t.m);
  }
  glm::vec3 operator()(const glm::vec3 &v) const;
  Ray operator()(const Ray &r) const;

public:
  glm::mat4 m;
  glm::mat4 mInv;
};

Transform Translate(const glm::vec3 &delta);

Transform Scale(float x, float y, float z);

Transform Rotate(float theta, const glm::vec3 &axis);

Transform LookAt(const glm::vec3 &pos, const glm::vec3 &look,
                 const glm::vec3 &up);

float Lerp(float t, float v1, float v2);

inline Transform operator*(Transform t1, const Transform t2) {
  return Transform(t1.m * t2.m, t2.mInv * t1.mInv);
}

inline Transform operator/(const Transform &t1, const Transform &t2) {
  Transform t2Inv = Inverse(t2);
  return Transform(t1.m * t2Inv.m, t2.mInv * t1.mInv);
}

#endif // EPQ_GEOMETRY_H
