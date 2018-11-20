//
// Created by Jesse Miettinen on 18/11/2018.
//

#ifndef PATH_TRACER_HITABLE_H
#define PATH_TRACER_HITABLE_H

#include <material/material.h>
#include "ray/ray.h"

class material;

struct hit_record{
    float time;
    vec3<float> point;
    vec3<float> normal;
    material *mat_ptr;
};

class hitable{
public:
    virtual bool hit(const ray<float>& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif //PATH_TRACER_HITABLE_H
