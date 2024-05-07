//
// Created by sohaibalam on 03/04/24.
//

#include "RNG.h"
#include <algorithm>

RNG::RNG() { SetSequence(0); }

void RNG::SetSequence(uint64_t sequenceIndex) {
  // We use the PCG random number generator
  state = 0u;
  inc = (sequenceIndex << 1u) | 1u;
  UniformUInt32();
  state += 0x853c49e6748fea9b;
  UniformUInt32();
}

uint32_t RNG::UniformUInt32() {
  uint64_t oldstate = state;
  state = oldstate * 6364136223846793005ULL + inc;
  uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
  uint32_t rot = oldstate >> 59u;
  return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

uint32_t RNG::UniformUInt32(uint32_t b) {
  uint32_t threshold = (~b + 1u) % b;
  while (true) {
    uint32_t r = UniformUInt32();
    if (r >= threshold)
      return r % b;
  }
}

float RNG::UniformFloat() {
  return std::min(OneMinusEpsilon, UniformUInt32() * 2.3283064365386963e-10f);
}