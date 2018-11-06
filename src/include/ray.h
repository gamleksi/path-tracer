//
// Created by Ville Leppälä on 6.11.2018.
//

#ifndef PATH_TRACER_RAY_H
#define PATH_TRACER_RAY_H

#include "vec3.h"

/* Ray is a function p(t) = A + t*b where A is the ray origin and B the
 * ray direction. t is a float parameter. P(t) describes a point at the ray.
 */


class ray
{
    public:
        ray() = default;
        ray(const vec3<float>& a, const vec3<float>& b)
        : A(a), B(b) { }

        vec3<float> origin() const {return A;}
        vec3<float> direction() const {return B;}
        vec3<float> point(float t) {return A + B * t;}
    private:
        vec3<float> A;
        vec3<float> B;

};

#endif //PATH_TRACER_RAY_H
