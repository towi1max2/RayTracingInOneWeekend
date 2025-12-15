#pragma once

#include "Ray.h"

class hit_record {
public:
    Vector3d m_Position;
    Vector3d m_Normal;
    double t;
};

class Hittable {
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};
