//
// Created by Elias on 9/24/2021.
//

#ifndef RAYTRACING_IMAGE_H
#define RAYTRACING_IMAGE_H

#include <memory>
#include <fstream>
#include "Color.h"

class Image {

private:
    uint32_t width;
    uint32_t height;
    Color* data;

public:
    explicit Image(uint32_t width, uint32_t height);
    ~Image();

    Image& Set(uint32_t x, uint32_t y, Color color);
    [[nodiscard]] Color& Get(uint32_t x, uint32_t y) const;
    [[nodiscard]] inline uint32_t GetWidth() const { return width; }
    [[nodiscard]] inline uint32_t GetHeight() const { return height; }

    void Write(const std::string& fileName) const;
};


#endif //RAYTRACING_IMAGE_H
