//
// Created by Elias on 9/25/2021.
//

#include "Material.h"
#include "Hittable.h"

Lambertian::Lambertian(const Vector3 &albedoColor) : albedo(albedoColor) {

}

bool Lambertian::Scatter(const Ray &ray, const HitRecord &record, Vector3 &attenuation, Ray &scattered) const {

    auto scatterDirection = record.Normal + Vector3::RandomUnit();

    if(scatterDirection.NearZero()) {

        scatterDirection  = record.Normal;
    }

    scattered = Ray{ record.Point, scatterDirection };
    attenuation = albedo;

    return true;
}

Metal::Metal(const Vector3 &albedoColor) : albedo(albedoColor) {

}

bool Metal::Scatter(const Ray &ray, const HitRecord &record, Vector3 &attenuation, Ray &scattered) const {

    auto reflected = Vector3::Reflect(ray.Direction().Unit(), record.Normal);
    scattered = Ray{ record.Point, reflected };
    attenuation = albedo;

    return (Vector3::Dot(scattered.Direction(), record.Normal) > 0);
}
