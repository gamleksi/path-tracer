//
// Created by Aleksi Hämäläinen on 14/11/2018.
//

#include "camera/camera.h"
#include "material/material.h"
#include "ray/ray.h"
#include "vector/vec3.h"
#include <limits>

Camera& Camera::operator = (const Camera& c) {
    u = c.u;
    v = c.v;
    origin_ = c.origin_;
    lower_left_corner_ = c.lower_left_corner_;
    horizontal_ = c.horizontal_;
    vertical_ = c.vertical_;
    lens_radius_ = c.lens_radius_;
    return *this;
};

Camera::Camera(const vec3<float>& look_from, const vec3<float>& look_at, const vec3<float>& view_up,
    float vfov, float aspect, float aperture, float dist_to_focus)
{
    lens_radius_ = aperture / float(200);
    float theta = vfov * float(M_PI/180);
    float half_height = tan(theta/2);
    float half_width = aspect * half_height;
    origin_ = look_from;
    vec3<float> w = (look_from - look_at).Unit();
    u = cross(view_up, w).Unit();
    v = cross(w, u);
    lower_left_corner_ = origin_ - dist_to_focus * (half_width * u + half_height*v + w);
    horizontal_ = half_width * 2 * u * dist_to_focus;
    vertical_ = half_height * 2* v * dist_to_focus;
}

vec3<float> Color(const ray<float>& r, const std::shared_ptr<Geometry>& geom, int depth)
{
    Hit_record rec;
    if (geom->RayHits(r, 0.001, std::numeric_limits<float>::max(), rec)) // TODO std::numeric_limits<float>::max() fix
    {
        ray<float> scattered;
        vec3<float> attenuation;
        vec3<float> emitted = rec.mat_ptr->Emitted(rec.u, rec.v, rec.point);
        if (depth < 50 && rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
        {
            return emitted + attenuation * Color(scattered, geom, depth+1);
        }
        else
        {
            return emitted;
        }
    }
    else
    {
        return vec3<float>(0,0,0);
    }



    /*Hit_record rec;

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
    }*/
}

vec3<float> NormalMapping(const ray<float>& r, const std::shared_ptr<Geometry>& geom)
{
  Hit_record rec{};
  if(geom->RayHits(r, 0.0, std::numeric_limits<float>::max(), rec)){ // TODO std::numeric_limits<float>::max() fix
    return (float)0.5*vec3<float>(rec.normal[0]+1,rec.normal[1]+1,rec.normal[2]+1);
  }else{
    vec3<float> unit_direction = r.Direction().Unit();
    float t = 0.5*(unit_direction[1]+1.0);
    return ((float)1.0-t)*vec3<float>(1.0,1.0,1.0) + t*vec3<float>(0.5,0.7,1.0);
  }

}


vec3<float> RandomUnitDiscCoord() {
    vec3<float> coord{}; // = (float)2.0 * vec3<float>((float)drand48(), (float)drand48(), 0) - vec3<float>(1.0, 1.0, 0.0);
    do {
      coord = (float) 2.0 * vec3<float>((float) drand48(), (float) drand48(), 0) - vec3<float>(1.0, 1.0, 0.0);
    } while(Dot(coord,coord) >= 1);
    return coord;
}

ray<float> Camera::GetRay(float s, float t) const {
    auto coord = RandomUnitDiscCoord() * lens_radius_;
    auto offset = u * coord[0] + v * coord[1];
    return {origin_+ offset, lower_left_corner_ + s * horizontal_ + t * vertical_ - origin_ - offset};
}

void Camera::ToJson(json & j){
    j["camera"]["Horizontal"]["x"] = GetHorizontal()[0];
    j["camera"]["Horizontal"]["y"] = GetHorizontal()[1];
    j["camera"]["Horizontal"]["z"] = GetHorizontal()[2];
    j["camera"]["Origin"]["x"] = GetOrigin()[0];
    j["camera"]["Origin"]["y"] = GetOrigin()[1];
    j["camera"]["Origin"]["z"] = GetOrigin()[2];
    j["camera"]["Vertical"]["x"] = GetVertical()[0];
    j["camera"]["Vertical"]["y"] = GetVertical()[1];
    j["camera"]["Vertical"]["z"] = GetVertical()[2];
    j["camera"]["LLC"]["x"] = GetLLC()[0];
    j["camera"]["LLC"]["y"] = GetLLC()[1];
    j["camera"]["LLC"]["z"] = GetLLC()[2];
    j["camera"]["U"]["x"] = GetU()[0];
    j["camera"]["U"]["y"] = GetU()[1];
    j["camera"]["U"]["z"] = GetU()[2];
    j["camera"]["V"]["x"] = GetV()[0];
    j["camera"]["V"]["y"] = GetV()[1];
    j["camera"]["V"]["z"] = GetV()[2];
    j["camera"]["LensRadius"] = GetLensRadius();
}