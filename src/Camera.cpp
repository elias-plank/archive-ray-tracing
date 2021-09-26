//
// Created by Elias on 9/25/2021.
//

#include "Camera.h"

Camera::Camera(const Vector3& position, const Vector3& lookAt, const Vector3& upDir, double vfov, double aspectRatio) {

    auto theta = DegreesToRadians(vfov);
    auto h = std::tan(theta / 2.0);
    auto viewportHeight = 2.0 * h;
    auto viewportWidth = aspectRatio * viewportHeight;

    auto w = (position - lookAt).Unit();
    auto u = Vector3::Cross(upDir, w).Unit();
    auto v = Vector3::Cross(w, u);

    origin = position;
    horizontal = u * viewportWidth;
    vertical = v * viewportHeight;
    lowerLeftCorner = origin - horizontal / 2.0 - vertical / 2.0 - w;
}

Ray Camera::GetRay(double s, double t) const {

    return Ray{ origin, lowerLeftCorner + horizontal * s + vertical * t - origin};
}


