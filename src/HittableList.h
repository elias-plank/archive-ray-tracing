//
// Created by Elias on 9/25/2021.
//

#ifndef RAYTRACING_HITTABLELIST_H
#define RAYTRACING_HITTABLELIST_H

#include "Hittable.h"
#include <memory>
#include <vector>

class HittableList : public Hittable {

private:
    std::vector<std::shared_ptr<Hittable>> objects{};

public:
    HittableList() = default;
    explicit HittableList(const std::shared_ptr<Hittable>& object);

    void Clear();
    void Add(const std::shared_ptr<Hittable>& object);

    [[nodiscard]] bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
};


#endif //RAYTRACING_HITTABLELIST_H
