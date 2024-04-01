//
// Created by sohaibalam on 01/04/24.
//

#ifndef EPQ_TRANSFORMATIONS_H
#define EPQ_TRANSFORMATIONS_H

#include <geometry.h>

/*
 * The files in geometricOperations define arithmetic operations between
 * geometric entities. This file defines operations with transformations.
 * */

Transform operator*(glm::vec<3, float, 0> t1, const Transform &t2) {
  return Transform(t1.m * t2.m, t2.mInv * t1.mInv);
}

Transform operator/(const Transform &t1, const Transform &t2) {
  return t1 * Inverse(t2);
}

#endif // EPQ_TRANSFORMATIONS_H
