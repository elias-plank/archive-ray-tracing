//
// Created by Elias on 9/24/2021.
//

#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include <cstdint>

#include "Vector3.h"

struct Color {

    uint8_t R{};
    uint8_t G{};
    uint8_t B{};

    [[nodiscard]] static Color FromVector3(const Vector3& vec, int32_t samplesPerPixel);
};

#endif //RAYTRACING_COLOR_H
