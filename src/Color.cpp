//
// Created by Elias on 9/25/2021.
//

#include "Color.h"
#include <algorithm>

Color Color::FromVector3(const Vector3 &vec, int32_t samplesPerPixel) {

    auto r = vec.X();
    auto g = vec.Y();
    auto b = vec.Z();

    auto scale = 1.0 / samplesPerPixel;
    r  = std::sqrt(scale * r);
    g  = std::sqrt(scale * g);
    b  = std::sqrt(scale * b);

    return {
        .R = static_cast<uint8_t>(256 * std::clamp(r, 0.0, 0.999)),
        .G = static_cast<uint8_t>(256 * std::clamp(g, 0.0, 0.999)),
        .B = static_cast<uint8_t>(256 * std::clamp(b, 0.0, 0.999))
    };
}
