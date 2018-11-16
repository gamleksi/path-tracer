//
// Created by Aleksi Hämäläinen on 14/11/2018.
//

#ifndef PATH_TRACER_CAMERA_H
#define PATH_TRACER_CAMERA_H

#include "ray/ray.h"
#include "geometry/geometry.h"



vec3<float> color(const ray<float>& r, Sphere& s);


#endif //PATH_TRACER_CAMERA_H
