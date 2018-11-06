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

vec3<float> color(const ray<float>& r);

#endif //PATH_TRACER_RAY_H
