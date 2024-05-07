//
// Created by sohaibalam on 03/04/24.
//

#include "stratifiedSampler.h"

void stratifiedSample1D(float *samples, int nSamples, bool jitter, RNG &rng) {
  float invNSamples = 1.0f / nSamples;
  for (int i = 0; i < nSamples; i++) {
    float delta = jitter ? rng.UniformFloat() : 0.5f;
    samples[i] = (i + delta) * invNSamples;
  }
}

// TODO: Come back and rewrite this
void stratifiedSample2D(glm::vec2 *samples, int nx, int ny, bool jitter,
                        RNG &rng) {
  float dx = 1.0f / nx, dy = 1.0f / ny;
  for (int y = 0; y < ny; ++y) {
    for (int x = 0; x < nx; ++x) {
      float jx = jitter ? rng.UniformFloat() : 0.5f;
      float jy = jitter ? rng.UniformFloat() : 0.5f;
      samples->x = (x + jx) * dx;
      samples->y = (y + jy) * dy;
      samples++;
    }
  }
}

template <typename T> void swap(T &a, T &b) {
  T temp = a;
  a = b;
  b = temp;
}

template <typename T>
void shuffle(T *samp, int count, int nDimensions, RNG &rng) {
  for (int i = 0; i < count; ++i) {
    int other = i + rng.UniformUInt32(count - i);
    for (int j = 0; j < nDimensions; ++j) {
      swap(samp[nDimensions * i + j], samp[nDimensions * other + j]);
    }
  }
}

void latinHypercube(float *samples, int nSamples, int nDimensions, RNG &rng) {
  float invNSamples = 1.0f / nSamples;
  for (int i = 0; i < nSamples; ++i) {
    for (int j = 0; j < nDimensions; ++j) {
      float sj = (i + (rng.UniformFloat())) * invNSamples;
      samples[nDimensions * i + j] = sj;
    }
  }
  for (int i = 0; i < nDimensions; ++i) {
    for (int j = 0; j < nSamples; ++j) {
      int other = j + rng.UniformUInt32(nSamples - j);
      std::swap(samples[nDimensions * j + i], samples[nDimensions * other + i]);
    }
  }
}

void stratifiedSampler::StartPixel(const glm::vec2 &p) {
  for (int i = 0; i < samples1D.size(); i++) {
    stratifiedSample1D(&samples1D[i][0], xPixelSamples * yPixelSamples,
                       jitterSamples, rng);
    shuffle(&samples1D[i][0], xPixelSamples * yPixelSamples, 1, rng);
  }
  for (int i = 0; i < samples2D.size(); i++) {
    stratifiedSample2D(&samples2D[i][0], xPixelSamples, yPixelSamples,
                       jitterSamples, rng);
    shuffle(&samples2D[i][0], xPixelSamples * yPixelSamples, 1, rng);
  }

  for (int i = 0; i < samples1DArraySizes.size(); i++) {
    for (int j = 0; j < samplesPerPixel; j++) {
      int count = samples1DArraySizes[i];
      stratifiedSample1D(&sampleArray1D[i][j * count], count, jitterSamples,
                         rng);
      shuffle(&sampleArray1D[i][j * count], count, 1, rng);
    }
  }

  for (size_t i = 0; i < samples2DArraySizes.size(); ++i) {
    for (int j = 0; j < samplesPerPixel; ++j) {
      int count = samples2DArraySizes[i];
      latinHypercube(&sampleArray2D[i][j * count].x, count, 2, rng);
    }
  }

  sampler::StartPixel(p);
}

std::unique_ptr<sampler> stratifiedSampler::Clone(int seed) {
  stratifiedSampler *ss = new stratifiedSampler(*this);
  ss->rng.SetSequence(seed);
  return std::unique_ptr<sampler>(ss);
}