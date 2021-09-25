//
// Created by Elias on 9/24/2021.
//

#include "Image.h"
#include <stdexcept>

Image::Image(uint32_t width, uint32_t height) : width(width), height(height) {

    data = new Color[width * height];
}

Image::~Image() {

    delete[] data;
}

Image &Image::Set(uint32_t x, uint32_t y, Color color) {

    data[y * width + x] = color;
    return *this;
}

Color& Image::Get(uint32_t x, uint32_t y) const {

    return data[y * width + x];
}

void Image::Write(const std::string &fileName) const {

    std::ofstream stream(fileName, std::ios_base::binary);

    if(stream.is_open()) {

        stream << "P6" << std::endl;
        stream << width << " " << height << std::endl;
        stream << 255 << std::endl;

        for(uint32_t y = 0; y < height; y++) {

            for(uint32_t x = 0; x < width; x++) {

                stream.write(reinterpret_cast<char*>(&this->Get(x, y)), sizeof(Color));
            }
            stream.flush();
        }
    }
    else {

        throw std::runtime_error("Couldn't open file");
    }
}
