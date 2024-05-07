//
// Created by sohaibalam on 01/04/24.
//

#ifndef EPQ_IMAGEIO_H
#define EPQ_IMAGEIO_H

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <stb_image.h>
#include <stb_image_write.h>

enum class ImageFormat {
    BMP,
    JPG,
    HDR
};

enum class ImageType {
    RGB,
    RGBA,
};

inline bool
writeImage(const std::string &filename, const unsigned char *data, int width, int height, ImageFormat format,
           ImageType type) {
    int channels = 0;
    switch (type) {
        case ImageType::RGB:
            channels = 3;
            break;
        case ImageType::RGBA:
            channels = 4;
            break;
    }

    switch (format) {
        case ImageFormat::BMP:
            return stbi_write_bmp(filename.c_str(), width, height, channels, data);
        case ImageFormat::JPG:
            return stbi_write_jpg(filename.c_str(), width, height, channels, data, 100);
        case ImageFormat::HDR:
            return stbi_write_hdr(filename.c_str(), width, height, channels, reinterpret_cast<const float *>(data));
    }


    return false;
}

#endif //EPQ_IMAGEIO_H
