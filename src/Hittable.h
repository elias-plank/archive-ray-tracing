//
// Created by Elias on 9/25/2021.
//

#ifndef RAYTRACING_HITTABLE_H
#define RAYTRACING_HITTABLE_H

#include "Ray.h"
#include <memory>

class Material;

struct HitRecord {

    Vector3 Point;
    Vector3 Normal;
    std::shared_ptr<Material> Material;
    double Time;
    bool FrontFace;

    void SetFaceNormal(const Ray& ray, const Vector3& outwardNormal);
};


class Hittable {

public:
    [[nodiscard]] virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
};


#endif //RAYTRACING_HITTABLE_H
