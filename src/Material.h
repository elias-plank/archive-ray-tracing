//
// Created by Elias on 9/25/2021.
//

#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

#include "Ray.h"

// Forward declaration
struct HitRecord;

class Material {

public:
    [[nodiscard]] virtual bool Scatter(const Ray& ray, const HitRecord& record, Vector3& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {

private:
    Vector3 albedo{};

public:
    explicit Lambertian(const Vector3& albedoColor);

    [[nodiscard]] bool Scatter(const Ray& ray, const HitRecord& record, Vector3& attenuation, Ray& scattered) const override;
};

class Metal : public Material {

private:
    Vector3 albedo{};

public:
    explicit Metal(const Vector3& albedoColor);

    [[nodiscard]] bool Scatter(const Ray& ray, const HitRecord& record, Vector3& attenuation, Ray& scattered) const override;

};

#endif //RAYTRACING_MATERIAL_H
