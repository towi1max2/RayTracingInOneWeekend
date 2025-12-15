#pragma once

#include "Hittable.h"
#include "Vector.h"

class sphere : public Hittable {
public:
    sphere(const Vector3d& center, double radius) : m_Center(center), m_Radius(std::fmax(0, radius)) {}

    bool hit(const Ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        vec3 oc = m_Center - r.GetOrigin();
        auto a = r.GetDirection().length_squared();
        auto h = dot(r.GetDirection(), oc);
        auto c = oc.length_squared() - m_Radius * m_Radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root) {
            root = (h + sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root)
                return false;
        }

        rec.t = root;
        rec.m_Position = r.at(rec.t);
        rec.m_Normal = (rec.m_Position - m_Center) / m_Radius;

        return true;
    }

private:
    Vector3d m_Center;
    double m_Radius;
};
