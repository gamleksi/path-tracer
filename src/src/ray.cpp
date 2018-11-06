//
// Created by Ville Leppälä on 6.11.2018.
//

#include <ray.h>
#include "vector/vec3.h"

vec3<float> color(const ray<float>& r)
{
    auto unit_direction = r.direction().unit();
    float t = (float)0.5 * (unit_direction[1] + (float)1.0);
    auto ray_vec = vec3<float>(1.0, 1.0, 1.0) * ((float)1.0 - t) + vec3<float>(0.5, 0.7, 1.0) * t;
    return ray_vec;
}