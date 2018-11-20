//
// Created by Jesse Miettinen on 14/11/2018.
//
#include "geometry/geometry.h"

bool Sphere::RayHits(const ray<float>& r, float t_min, float t_max, hit_record& rec) const
{
    vec3<float> pos = GetPosition();
    vec3<float> oc = r.origin() - pos;
    float a = dot(r.direction(), r.direction());
    float b = (float)2.0 * dot(oc, r.direction());
    float c = dot(oc,oc) - radius_*radius_;
    float discriminant = b*b - 4*a*c;
    //float res;
    if (discriminant > 0){
        float temp = (-b - sqrtf(discriminant))/(2 * a);
        if (temp < t_max && temp > t_min){
            rec.time = temp;
            rec.point = r.point((temp));
            rec.normal = (rec.point-pos) / GetRadius();
            return true;
        }
        temp = (-b + sqrtf(discriminant))/( 2 * a);
        if (temp < t_max && temp > t_min){
            rec.time = temp;
            rec.point = r.point(temp);
            rec.normal = (rec.point - pos) / GetRadius();
            return true;
        }
    }
    return false;
}
