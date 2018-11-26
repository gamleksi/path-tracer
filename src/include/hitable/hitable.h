//
// Created by Aleksi Hämäläinen on 26/11/2018.
//

#ifndef PATH_TRACER_HITABLE_H
#define PATH_TRACER_HITABLE_H

#include "vector/vec3.h"
#include "ray/ray.h"

class Material;

struct Hit_record{
  float time;
  vec3<float> point;
  vec3<float> normal;
  Material* mat_ptr;
};

#endif //PATH_TRACER_HITABLE_H
