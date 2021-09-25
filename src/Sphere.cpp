//
// Created by Elias on 9/25/2021.
//

#include "Sphere.h"

Sphere::Sphere(const Vector3 &center, double radius, std::shared_ptr<Material> material) : center(center), radius(radius), material(std::move(material)) {


}

bool Sphere::Hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const {

    Vector3 oc = ray.Origin() - center;
    auto a = ray.Direction().Length2();
    auto bHalf = Vector3::Dot(oc, ray.Direction());
    auto c = oc.Length2() - radius * radius;

    auto discriminant = bHalf * bHalf - a * c;
    if (discriminant < 0) return false;
    auto sqrtDiscriminant = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-bHalf - sqrtDiscriminant) / a;

    if (root < tMin || tMax < root) {

        root = (-bHalf + sqrtDiscriminant) / a;

        if (root < tMin || tMax < root) {

            return false;
        }
    }

    record.Time = root;
    record.Point = ray.At(record.Time);
    Vector3 outwardNormal = (record.Point - center) / radius;
    record.SetFaceNormal(ray, outwardNormal);
    record.Material = material;

    return true;
}
