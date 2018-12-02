//
// Created by Aleksi Hämäläinen on 14/11/2018.
//

#include "camera/camera.h"
#include "material/material.h"
#include "ray/ray.h"
#include "vector/vec3.h"

Camera::Camera(const vec3<float>& look_from, const vec3<float>& look_at, const vec3<float>& view_up, float vfov, float aspect)
{
    float theta = vfov * float(M_PI/180);
    float half_height = tan(theta/2);
    float half_width = aspect * half_height;
    origin_ = look_from;
    vec3<float> w = (look_from - look_at).Unit();
    vec3<float> u = cross(view_up, w).Unit();
    vec3<float> v = cross(w, u);
    lower_left_corner_ = vec3<float>(-half_width, -half_height, float(-1.0));
    lower_left_corner_ = origin_ - half_width*u - half_height*v - w;
    horizontal_ = half_width * 2 * u;
    vertical_ = half_height * 2* v;
}

vec3<float> Color(const ray<float>& r, const std::shared_ptr<Geometry>& geom, int depth)
{
    Hit_record rec;

    if(geom->RayHits(r, 0.000001, MAXFLOAT, rec)){
        ray<float> scattered{};
        vec3<float> attenuation{};
        if (depth < 50 && rec.mat_ptr->Scatter(r, rec, attenuation, scattered)) {
            return attenuation * Color(scattered, geom, depth+1);
        } else {
            return vec3<float>(0,0,0);
        }
    } else {
        vec3<float> unit_direction = r.Direction().Unit();
        float t = (float)0.5*(unit_direction[1]+ (float)1.0);
        return ((float)1.0-t)*vec3<float>(1.0,1.0,1.0) + t*vec3<float>(0.5,0.7,1.0);
    }
}
