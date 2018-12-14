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


class Camera {
public:

    /*look_from is a point where we are looking from
     *look_at is a point where we are looking at
     * view_up is a vector up from the point we are looking, determines rotation of the camera on the axis from camera to the point we are looking into
     */
    Camera(const vec3<float>& look_from, const vec3<float>& look_at, const vec3<float>& view_up,
    float vfov, float aspect, float aperture, float dist_to_focus);
    ray<float> GetRay(float u, float v) const;

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
