//
// Created by Jesse Miettinen on 14/11/2018.
//
#include "geometry/geometry.h"

float Sphere::RayHits(const ray<float>& r) {
    vec3<float> pos = GetPosition();
    vec3<float> oc = r.origin() - pos;
    float a = dot(r.direction(), r.direction()); // function should be called dot, instead of cross
    float b = (float)2.0 * dot(oc, r.direction());
    float c = dot(oc,oc) - radius_*radius_;
    float discriminant = b*b - 4*a*c;
    float res;
    if (discriminant < 0){
        res = -(float)1.0;
    }
    else{
        res = (-b - sqrtf(discriminant)/((float)2.0*a));
    }
    return res;
}