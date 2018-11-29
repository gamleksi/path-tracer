//
// Created by Aleksi Hämäläinen on 14/11/2018.
//

#include "camera/camera.h"
<<<<<<< src/include/camera/camera.cpp
#include "material/material.h"
#include "ray/ray.h"
#include "vector/vec3.h"

Camera::Camera(vec3<float> look_from, vec3<float> look_at, vec3<float> view_up, float vfov, float aspect)
{
    float theta = vfov * float(M_PI/180);
    float half_height = tan(theta/2);
    float half_width = aspect * half_height;
    origin_ = look_from;
    vec3<float> w = (look_from - look_at).unit();
    vec3<float> u = cross(view_up, w).unit();
    vec3<float> v = cross(w, u);
    lower_left_corner_ = vec3<float>(-half_width, -half_height, float(-1.0));
    lower_left_corner_ = origin_ - half_width*u - half_height*v - w;
    horizontal_ = half_width * 2 * u;
    vertical_ = half_height * 2* v;
}


ray<float> Camera::GetRay(float u, float v) {
    ray<float> ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    return ray;
}

vec3<float> color(const ray<float>& r, Geometry* geom, int depth)
{
    Hit_record rec;

    if(geom->RayHits(r, 0.000001, MAXFLOAT, rec)){
        ray<float> scattered;
        vec3<float> attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, geom, depth+1);
        } else {
            return vec3<float>(0,0,0);
        }
    } else {
        vec3<float> unit_direction = r.direction().unit();
        float t = (float)0.5*(unit_direction[1]+1.0);
        return ((float)1.0-t)*vec3<float>(1.0,1.0,1.0) + t*vec3<float>(0.5,0.7,1.0);
    }
}
