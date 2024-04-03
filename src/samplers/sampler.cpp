//
// Created by sohaibalam on 02/04/24.
//

#include "sampler.h"
#include "cameras/camera.h"

CameraSample sampler::GetCameraSample(const glm::vec2 &pRaster) {
  CameraSample cs{};
  cs.pFilm = pRaster + Get2D();
  cs.time = Get1D();
  cs.pLens = Get2D();
  return cs;
}

void sampler::StartPixel(const glm::vec2 &p) {
  currentPixel = p;
  currentPixelSampleIndex = 0;
  array1DOffset = array2DOffset = 0;
}

bool sampler::StartNextSample() {
  array1DOffset = array2DOffset = 0;
  return ++currentPixelSampleIndex < samplesPerPixel;
}

bool sampler::setSampleNumber(int64_t sampleNum) {
  array1DOffset = array2DOffset = 0;
  currentPixelSampleIndex = sampleNum;
  return currentPixelSampleIndex < samplesPerPixel;
}

void sampler::Request1DArray(int n) {
  samples1DArraySizes.push_back(n);
  sampleArray1D.emplace_back(n * samplesPerPixel);
}

void sampler::Request2DArray(int n) {
  samples2DArraySizes.push_back(n);
  sampleArray2D.emplace_back(n * samplesPerPixel);
}

const float *sampler::Get1DArray(int n) {
  if (array1DOffset == sampleArray1D.size())
    return nullptr;
  return &sampleArray1D[array1DOffset++][currentPixelSampleIndex * n];
}

const glm::vec2 *sampler::Get2DArray(int n) {
  if (array2DOffset == sampleArray2D.size())
    return nullptr;
  return &sampleArray2D[array2DOffset++][currentPixelSampleIndex * n];
}

// Pixel Sampler Implementation

pixelSampler::pixelSampler(int64_t samplesPerPixel, int nSampledDimensions)
    : sampler(samplesPerPixel) {
  for (int i = 0; i < nSampledDimensions; ++i) {
    samples1D.emplace_back(samplesPerPixel);
    samples2D.emplace_back(samplesPerPixel);
  }
}

bool pixelSampler::StartNextSample() {
  current1DDimension = current2DDimension = 0;
  return sampler::StartNextSample();
}

bool pixelSampler::setSampleNumber(int64_t sampleNum) {
  current1DDimension = current2DDimension = 0;
  return sampler::setSampleNumber(sampleNum);
}

float pixelSampler::Get1D() {
  if (current1DDimension < samples1D.size())
    return samples1D[current1DDimension++][currentPixelSampleIndex];
  return rng.UniformFloat();
}

glm::vec2 pixelSampler::Get2D() {
  if (current2DDimension < samples2D.size())
    return samples2D[current2DDimension++][currentPixelSampleIndex];
  return {rng.UniformFloat(), rng.UniformFloat()};
}

// Global Sampler Implementation

void globalSampler::StartPixel(const glm::vec2 &p) {
  sampler::StartPixel(p);
  dimension = 0;
  intervalSampleIndex = GetIndexForSample(0);
  arrayEndDim = arrayStartDim + samples1DArraySizes.size() +
                2 * samples2DArraySizes.size();
  for (size_t i = 0; i < sampleArray1D.size(); ++i) {
    int nSamples = samples1DArraySizes[i] * samplesPerPixel;
    for (size_t j = 0; j < sampleArray1D[i].size(); ++j) {
      int64_t index = GetIndexForSample(j);
      sampleArray1D[i][j] = SampleDimension(index, arrayStartDim + dimension);
    }
  }

  // same for 2D
  int dim = arrayStartDim + samples1DArraySizes.size();
  for (size_t i = 0; i < sampleArray2D.size(); ++i) {
    int nSamples = samples2DArraySizes[i] * samplesPerPixel;
    for (size_t j = 0; j < sampleArray2D[i].size(); ++j) {
      int64_t index = GetIndexForSample(j);
      sampleArray2D[i][j].x = SampleDimension(index, dim);
      sampleArray2D[i][j].y = SampleDimension(index, dim + 1);
    }
    dim += 2;
  }
  assert(dim == arrayEndDim);
}

bool globalSampler::StartNextSample() {
  dimension = 0;
  intervalSampleIndex = GetIndexForSample(currentPixelSampleIndex + 1);
  return sampler::StartNextSample();
}

bool globalSampler::setSampleNumber(int64_t sampleNum) {
  dimension = 0;
  intervalSampleIndex = GetIndexForSample(sampleNum);
  return sampler::setSampleNumber(sampleNum);
}

float globalSampler::Get1D() {
  if (dimension >= arrayStartDim && dimension < arrayEndDim)
    return SampleDimension(intervalSampleIndex, dimension++);
  return SampleDimension(intervalSampleIndex, dimension++);
}

glm::vec2 globalSampler::Get2D() {
  if (dimension + 1 >= arrayStartDim && dimension < arrayEndDim)
    dimension = arrayEndDim;
  glm::vec2 p(SampleDimension(intervalSampleIndex, dimension),
              SampleDimension(intervalSampleIndex, dimension + 1));
  dimension += 2;
  return p;
}