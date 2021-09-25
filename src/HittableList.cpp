//
// Created by Elias on 9/25/2021.
//

#include "HittableList.h"

HittableList::HittableList(const std::shared_ptr<Hittable> &object) : HittableList() {

    Add(object);
}

void HittableList::Clear() {

    objects.clear();
}

void HittableList::Add(const std::shared_ptr<Hittable> &object) {

    objects.push_back(object);
}

bool HittableList::Hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const {

    HitRecord tmpRecord{};
    bool hitAnything = false;
    auto closest = tMax;

    for(const auto& object : objects) {

        if(object->Hit(ray, tMin, closest, tmpRecord)) {

            hitAnything = true;
            closest = tmpRecord.Time;
            record = tmpRecord;
        }
    }

    return hitAnything;
}
