//
// Created by Jesse Miettinen on 14/11/2018.
//
#include "geometry/geometry.h"

Sphere::Sphere(vec3<float> position, float radius, std::shared_ptr<Material> mat)
    : Geometry(), radius_(radius), position_(position), material_(std::move(mat)) { }

bool Sphere::RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const
{
    vec3<float> pos = GetPosition();
    vec3<float> oc = r.Origin() - pos;
    float a = Dot(r.Direction(), r.Direction());
    float b = (float)2.0 * Dot(oc, r.Direction());
    float c = Dot(oc,oc) - radius_*radius_;
    float discriminant = b*b - 4*a*c;
    if (discriminant > 0){
        float temp = (-b - sqrtf(discriminant))/(2 * a);
        if (temp < t_max && temp > t_min){
            rec.time = temp;
            rec.point = r.Point((temp));
            rec.normal = (rec.point-pos) / GetRadius();
            rec.mat_ptr = material_;
            return true;
        }
        temp = (-b + sqrtf(discriminant))/( 2 * a);
        if (temp < t_max && temp > t_min){
            rec.time = temp;
            rec.point = r.Point(temp);
            rec.normal = (rec.point - pos) / GetRadius();
            rec.mat_ptr = material_;
            return true;
        }
    }
    return false;
}



bool Geomlist::RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const{
    Hit_record temp_rec{};
    bool hit = false;
    float closest_distance = t_max;
    for (int i = 0; i < list_size_; i++){
        if(list_[i]->RayHits(r, t_min, closest_distance, temp_rec)){
            hit = true;
            closest_distance = temp_rec.time;
            rec = temp_rec;
        }
    }
    return hit;
}

