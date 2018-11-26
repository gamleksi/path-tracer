//
// Created by Aleksi Hämäläinen on 14/11/2018.
//

#include "camera/camera.h"
#include "material/material.h"

#include "ray/ray.h"


vec3<float> color(const ray<float>& r, Geometry *world, int depth)
{
    hit_record rec;

    if(world->RayHits(r, 0.000001, MAXFLOAT, rec)){
        ray<float> scattered;
        vec3<float> attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec,attenuation, scattered)){
            return attenuation*color(scattered, world, depth+1);
        } else {
            return vec3<float>(0,0,0);
        }
    }else{
        vec3<float> unit_direction = r.direction().unit();
        float t = 0.5*(unit_direction[1]+1.0);
        return ((float)1.0-t)*vec3<float>(1.0,1.0,1.0) + t*vec3<float>(0.5,0.7,1.0);
    }
}