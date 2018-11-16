//
// Created by Aleksi Hämäläinen on 14/11/2018.
//

#include "camera/camera.h"
//#include "ray/ray.h"
//#include "geometry/geometry.h"

vec3<float> color(const ray<float>& r, Sphere& s)
{

    float t = s.RayHits(r);
    if(t>0.0){
        vec3<float> N = (r.point(t) - s.GetPosition()).unit();
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