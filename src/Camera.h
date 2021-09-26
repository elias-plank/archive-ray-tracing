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
    Camera(const Vector3& position, const Vector3& lookAt, const Vector3& upDir, double vfov, double aspectRatio);

    [[nodiscard]] Ray GetRay(double s, double t) const;
};


#endif //RAYTRACING_CAMERA_H
