//
// Created by Ville Leppälä on 6.11.2018.
//

#ifndef PATH_TRACER_RAY_H
#define PATH_TRACER_RAY_H

#include "vector/vec3.h"

template <typename T>
class ray
{
    public:
        ray() = default;

        ray(const vec3<T>& a, const vec3<T>& b)
        : A(a), B(b) { }

        vec3<T> origin() const {return A;}
        vec3<T> direction() const {return B;}
        vec3<T> point( const T t) {return A + B * t;}
    private:
        vec3<T> A;
        vec3<T> B;

};

vec3<float> color(const ray<float>& r)
{
    auto unit_direction = r.direction().unit();
    float t = (float)0.5 * (unit_direction[1] + (float)1.0);
    auto ray_vec = vec3<float>(1.0, 1.0, 1.0) * ((float)1.0 - t) + vec3<float>(0.5, 0.7, 1.0) * t;
    return ray_vec;
}

#endif //PATH_TRACER_RAY_H
