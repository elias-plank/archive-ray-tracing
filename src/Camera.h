//
// Created by Elias on 9/25/2021.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "Ray.h"

class Camera {

private:
    Vector3 origin{};
    Vector3 lowerLeftCorner{};
    Vector3 horizontal{};
    Vector3 vertical{};

public:
    Camera() = delete;
    explicit Camera(double aspectRatio, double focalLength = 1.0);

    [[nodiscard]] Ray GetRay(double u, double v) const;
};


#endif //RAYTRACING_CAMERA_H
