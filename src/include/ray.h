//
// Created by Ville Leppälä on 6.11.2018.
//

#ifndef PATH_TRACER_RAY_H
#define PATH_TRACER_RAY_H

#include "vector/vec3.h"
#include "geometry/geometry.h"


template <typename T>
class ray
{
    public:
        ray() = default;

        ray(const vec3<T>& a, const vec3<T>& b)
        : A(a), B(b) { }

        vec3<T> origin() const {return A;}
        vec3<T> direction() const {return B;}
        vec3<T> point(T t) {return A + B * t;}
    private:
        vec3<T> A;
        vec3<T> B;

};

vec3<float> color(const ray<float>& r, Sphere* s)
{
    float t = s->RayHits(r);
    if(t>0.0){
        vec3<float> N = (r.point(t) - s->get_Position()).unit();
        return (float)0.5*vec3<float>(N[0]+1,N[1]+1,N[2]+1);
    }
    vec3<float> unit_direction = r.direction().unit();
    t = (float)0.5*(unit_direction[1]+(float)1.0);
    return ((float)1.0-t)*vec3<float>(1.0,1.0,1.0) + t*vec3<float>(0.5,0.7,1.0);

    //auto unit_direction = r.direction().unit();
    //float t = (float)0.5 * (unit_direction[1] + (float)1.0);
    //auto ray_vec = vec3<float>(1.0, 1.0, 1.0) * ((float)1.0 - t) + vec3<float>(0.5, 0.7, 1.0) * t;
    //return ray_vec;
}

#endif //PATH_TRACER_RAY_H
