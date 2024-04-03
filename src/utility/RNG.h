//
// Created by sohaibalam on 03/04/24.
//

#ifndef EPQ_RNG_H
#define EPQ_RNG_H

// modelled after PCG pseudo-random number generator

#include <cstdint>

static const float OneMinusEpsilon = 0x1.fffffep-1;

class RNG {
public:
  RNG();
  RNG(uint64_t sequenceIndex) { SetSequence(sequenceIndex); }

  void SetSequence(uint64_t sequenceIndex);

  uint32_t UniformUInt32();
  uint32_t UniformUInt32(uint32_t b);
  float UniformFloat();

private:
  uint64_t state, inc;
};

#endif // EPQ_RNG_H
