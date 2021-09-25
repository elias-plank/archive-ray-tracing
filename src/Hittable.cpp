//
// Created by Elias on 9/25/2021.
//

#include "Hittable.h"

void HitRecord::SetFaceNormal(const Ray &ray, const Vector3& outwardNormal) {

    FrontFace = Vector3::Dot(ray.Direction(), outwardNormal) < 0;
    Normal = FrontFace ? outwardNormal : -outwardNormal;
}
