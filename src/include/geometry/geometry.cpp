//
// Created by Jesse Miettinen on 14/11/2018.
//
#include "geometry/geometry.h"

bool Sphere::RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const
{
    vec3<float> pos = GetPosition();
    vec3<float> oc = r.origin() - pos;
    float a = dot(r.direction(), r.direction()); // function should be called dot, instead of cross
    float b = (float)2.0 * dot(oc, r.direction());
    float c = dot(oc,oc) - radius_*radius_;
    float discriminant = b*b - 4*a*c;
    //float res;
    if (discriminant > 0){
        float temp = (-b - sqrtf(b*b-a*c))/a; // Isn't this supposed to be: -b - sqrtf(b*b - 4 * a * c)/ (2*a)
        if (temp < t_max && temp > t_min){
            rec.time = temp;
            rec.point = r.point((temp));
            rec.normal = (rec.point-pos)/GetRadius(); //why do we have to divide by radius? Is this cause we want unit length vector?
            return true;
        }
        temp = (-b + sqrtf(b*b-a*c))/a; //here again different from literature
        if (temp < t_max && temp > t_min){
            rec.time = temp;
            rec.point = r.point(temp);
            rec.normal = (rec.point - pos) / GetRadius();
            return true;
        }
        //res = -(float)1.0;
    }
    return false;
}

bool Geomlist::RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const{
    Hit_record temp_rec;
    bool hit = false;
    double closest_distance = t_max;
    for (int i = 0; i < list_size_; i++){
        if(list_[i]->RayHits(r, t_min, closest_distance, temp_rec)){
            hit = true;
            closest_distance = temp_rec.time;
            rec = temp_rec; //this line does not make sense.
        }
    }
    return hit;
}
