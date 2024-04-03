#include "imageio.h"
#include <iostream>

/*
 * This project is the implementation of my EPQ project, this entails creating a
 * physically based renderer following the principles outlined in the book
 * "Physically Based Rendering: From Theory to Implementation" by Matt Pharr and
 * Greg Humphreys. The project will be implemented in C++ and will output a
 * high-quality image as part of its runtime.
 *
 * The project will be implemented in a modular fashion, with the following
 * modules:
 *
 * 1. Image I/O  - Completed as of 01-04
 * 2. Geometry
 * 3. Materials
 * 4. Lights
 * 5. Cameras
 * 6. Integrators
 * 7. Samplers
 * 8. Acceleration Structures
 * 9. Scene
 * 10. Renderer
 *
 *
 * How the project will work for a very basic scene:
 * - The scene will be created with a camera, a light source, and a sphere.
 * (This could use an external file to describe the scene)
 * - The renderer will be created with a sampler, an integrators, and an
 * acceleration structure.
 * - The integrators will take a ray from the camera, and intersect it with the
 * scene.
 * - The integrators will then calculate the colour of the pixel based on the
 * intersection point.
 * - This will happen firstly by calculating the direct lighting, and then the
 * indirect lighting.
 * - Indirect lighting will be calculated by sampling the hemisphere around the
 * intersection point.
 * - The sampler will be used to sample the hemisphere.
 * - Direct lighting will be calculated by sampling the light source, and using
 * the BxDFs to calculate the colour.
 * - The BxDFs can be implemented by following Pixar's or Disney's BRDFs.
 * - The renderer will output the image.
 *
 *  The project will be implemented in C++ and will use the following libraries:
 *  - stb_image.h
 *  - stb_image_write.h
 *  - glm
 *  - OpenMP
 *
 *  The following things will be implemented in order:
 *  - Image I/O - Completed as of 01-04
 *  - Cameras
 *  - Geometry
 *  - Scene
 *  - (Basic) Integrators
 *  - Samplers
 *  - Materials
 *  - Lights
 *  - Acceleration Structures
 *  - Film
 *
 * */

int main() {
  unsigned char *data = new unsigned char[3 * 256 * 256];
  for (int i = 0; i < 3 * 256 * 256; i++) {
    data[i] = 255;
  }
  writeImage("test.bmp", data, 256, 256, ImageFormat::BMP, ImageType::RGB);
  delete[] data;
}
