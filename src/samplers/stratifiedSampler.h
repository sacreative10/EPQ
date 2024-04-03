//
// Created by sohaibalam on 03/04/24.
//

#ifndef EPQ_STRATIFIEDSAMPLER_H
#define EPQ_STRATIFIEDSAMPLER_H

#include <samplers/sampler.h>

class stratifiedSampler : public pixelSampler {
public:
  stratifiedSampler(int xPixelSamples, int yPixelSamples, bool jitterSamples,
                    int nSampledDimensions)
      : pixelSampler(xPixelSamples * yPixelSamples, nSampledDimensions),
        xPixelSamples(xPixelSamples), yPixelSamples(yPixelSamples),
        jitterSamples(jitterSamples) {}

  void StartPixel(const glm::vec2 &p);
  std::unique_ptr<sampler> Clone(int seed);

private:
  const int xPixelSamples, yPixelSamples;
  const bool jitterSamples;
};
#endif // EPQ_STRATIFIEDSAMPLER_H
