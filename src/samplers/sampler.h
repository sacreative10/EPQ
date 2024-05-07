//
// Created by sohaibalam on 02/04/24.
//

#ifndef EPQ_SAMPLER_H
#define EPQ_SAMPLER_H

#include "utility/RNG.h"
#include <cstddef>
#include <geometry.h>
#include <memory>

struct CameraSample;

class sampler {
public:
  ~sampler() {}
  sampler(int64_t samplesPerPixel) : samplesPerPixel(samplesPerPixel) {}
  virtual void StartPixel(const glm::vec2 &p);
  virtual float Get1D() = 0;
  virtual glm::vec2 Get2D() = 0;
  virtual bool StartNextSample();
  CameraSample GetCameraSample(const glm::vec2 &pRaster);
  void Request1DArray(int n);
  void Request2DArray(int n);
  virtual int RoundCount(int n) const { return n; }
  const float *Get1DArray(int n);
  const glm::vec2 *Get2DArray(int n);
  virtual std::unique_ptr<sampler> Clone(int seed) = 0;
  virtual bool setSampleNumber(int64_t sampleNum);

public:
  const int64_t samplesPerPixel;

protected:
  glm::vec2 currentPixel;
  int currentPixelSampleIndex;
  std::vector<int> samples1DArraySizes, samples2DArraySizes;
  std::vector<std::vector<float>> sampleArray1D;
  std::vector<std::vector<glm::vec2>> sampleArray2D;

private:
  size_t array1DOffset, array2DOffset;
};

class pixelSampler : public sampler {
public:
  pixelSampler(int64_t samplesPerPixel, int nSampledDimensions);
  bool StartNextSample() override;
  bool setSampleNumber(int64_t sampleNum) override;
  float Get1D() override;
  glm::vec2 Get2D() override;

protected:
  std::vector<std::vector<float>> samples1D;
  std::vector<std::vector<glm::vec2>> samples2D;
  size_t current1DDimension = 0, current2DDimension = 0;
  RNG rng;
};

class globalSampler : public sampler {
public:
  bool StartNextSample();
  void StartPixel(const glm::vec2 &p);
  bool setSampleNumber(int64_t sampleNum);
  float Get1D();
  glm::vec2 Get2D();
  globalSampler(int64_t samplesPerPixel, int nSampledDimensions);
  virtual int64_t GetIndexForSample(int64_t sampleNum) const = 0;
  virtual float SampleDimension(int64_t index, int dimension) const = 0;

private:
  int dimension;
  int64_t intervalSampleIndex;
  static const int arrayStartDim = 5;
  int arrayEndDim;
};

#endif // EPQ_SAMPLER_H
