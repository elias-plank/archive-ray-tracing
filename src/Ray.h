//
// Created by Elias on 9/25/2021.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include "Vector3.h"

class Ray {

private:
    Vector3 origin;
    Vector3 direction;

public:
    Ray() = default;
    Ray(const Vector3& origin, const Vector3& direction);

    [[nodiscard]] inline Vector3 Origin() const { return origin; }
    [[nodiscard]] inline Vector3 Direction() const { return direction; }
    [[nodiscard]] inline Vector3 At(double t) const { return origin + direction * t; }
};


#endif //RAYTRACING_RAY_H
