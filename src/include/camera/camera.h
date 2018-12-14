//
// Created by Aleksi Hämäläinen on 14/11/2018.
//

#ifndef PATH_TRACER_CAMERA_H
#define PATH_TRACER_CAMERA_H

#include <memory>
#include "vector/vec3.h"
#include "geometry/geometry.h"
#include "material/material.h"
#include "ray/ray.h"
#include <nlohmann/json.hpp>
// for convenience
using json = nlohmann::json;


class Camera {
public:

    /*look_from is a point where we are looking from
     *look_at is a point where we are looking at
     * view_up is a vector up from the point we are looking, determines rotation of the camera on the axis from camera to the point we are looking into
     */
    Camera(const vec3<float>& look_from, const vec3<float>& look_at, const vec3<float>& view_up,
    float vfov, float aspect, float aperture, float dist_to_focus);

    //loader constructor
    Camera(vec3<float>& u, vec3<float>& v,vec3<float>& origin_,vec3<float>& llc, vec3<float>& hor, vec3<float>& ver,float lens_radius)
    : u(u), v(v), origin_(origin_), lower_left_corner_(llc), horizontal_(hor), vertical_(ver), lens_radius_(lens_radius){}

    ray<float> GetRay(float u, float v) const;

    //getter functions for saving camera
    vec3<float> GetU()const{return u;}
    vec3<float> GetV()const{return v;}
    vec3<float> GetOrigin()const{return origin_;}
    vec3<float> GetLLC()const{return lower_left_corner_;}
    vec3<float> GetHorizontal()const{return horizontal_;}
    vec3<float> GetVertical()const{return vertical_;}
    float GetLensRadius()const{return lens_radius_;}

    void ToJson(json & j);

private:
    vec3<float> u;
    vec3<float> v;
    vec3<float> origin_;
    vec3<float> lower_left_corner_;
    vec3<float> horizontal_;
    vec3<float> vertical_;
    float lens_radius_;
};

vec3<float> Color(const ray<float>& r, const std::shared_ptr<Geometry>& geom, int depth);

vec3<float> NormalMapping(const ray<float>& r, const std::shared_ptr<Geometry>& geom);

vec3<float> RandomUnitDiscCoord();


#endif //PATH_TRACER_CAMERA_H
