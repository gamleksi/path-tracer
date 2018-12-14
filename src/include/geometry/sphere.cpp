//
// Created by Aleksi Hämäläinen on 14/12/2018.
//

#include "sphere.h"

int Sphere::NumberOfObjects() const {
  return 1;
}

Sphere::Sphere(vec3<float> position, float radius, std::shared_ptr<Material> mat)
    : Geometry(), radius_(radius), position_(position), material_(std::move(mat)) { }

bool Sphere::RayHits(const ray<float>& r, float t_min, float t_max, HitRecord& rec) const
{
    vec3<float> oc = r.Origin() - position_;
    float a = Dot(r.Direction(), r.Direction());
    float b = Dot(oc, r.Direction());
    float c = Dot(oc,oc) - radius_*radius_;
    float discriminant = b*b - a*c;
    if (discriminant > 0){
        float temp = (-b - sqrtf(discriminant))/(a);
        if (temp < t_max && temp > t_min){
            rec.time = temp;
            rec.point = r.Point(rec.time);
            rec.normal = (rec.point - position_) / radius_;
            rec.mat_ptr = material_;
            return true;
        }
        temp = (-b + sqrtf(discriminant))/(a);
        if (temp < t_max && temp > t_min){
            rec.time = temp;
            rec.point = r.Point(rec.time);
            rec.normal = (rec.point - position_) / radius_;
            rec.mat_ptr = material_;
            return true;
        }
    }
    return false;
}

bool Sphere::GetBoundingBox(float t0, float t1, BoundingBox& box) const {
    box = BoundingBox(position_ - radius_, position_ + radius_);
    return true;
}
