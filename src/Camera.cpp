//
// Created by Elias on 9/25/2021.
//

#include "Camera.h"

Camera::Camera(double aspectRatio, double focalLength) {

    auto viewportHeight = 2.0;
    auto viewportWidth = aspectRatio * viewportHeight;

    origin = Vector3{0, 0, 0};
    horizontal = Vector3{ viewportWidth, 0, 0 };
    vertical = Vector3{0, viewportHeight, 0 };
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vector3{ 0, 0, focalLength};
}

Ray Camera::GetRay(double u, double v) const {

    return Ray{ origin, lowerLeftCorner + horizontal * u + vertical * v - origin};
}


