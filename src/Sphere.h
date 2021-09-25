//
// Created by Elias on 9/25/2021.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include "Hittable.h"

class Sphere : public Hittable {

private:
    Vector3 center{};
    double radius{};
    std::shared_ptr<Material> material{};

public:
    Sphere() = default;
    Sphere(const Vector3& center, double radius, std::shared_ptr<Material> material);

    [[nodiscard]] bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
};


#endif //RAYTRACING_SPHERE_H
