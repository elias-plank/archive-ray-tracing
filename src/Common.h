//
// Created by Elias on 9/25/2021.
//

#ifndef RAYTRACING_COMMON_H
#define RAYTRACING_COMMON_H

#include <limits>
#include <random>

static constexpr double Infinity = std::numeric_limits<double>::infinity();
static constexpr double PI = 3.1415926535897;

inline static constexpr double DegreesToRadians(double degrees) {

    return degrees * PI / 180.0;
}

inline static double RandomDouble(double min, double max) {

    static std::random_device RandomDevice;
    static std::mt19937_64 RandomMt(RandomDevice());
    std::uniform_real_distribution<double> dist(min, max);

    return dist(RandomMt);
}

inline static double RandomDouble() {

    return RandomDouble(0.0, 1.0);
}

#endif //RAYTRACING_COMMON_H
