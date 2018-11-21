//
// Created by Aleksi Hämäläinen on 14/11/2018.
//

#ifndef PATH_TRACER_CAMERA_H
#define PATH_TRACER_CAMERA_H

#include "ray/ray.h"
#include "geometry/geometry.h"

class Camera {
public:
    Camera(float vfov, float aspect)
    {
        float theta = vfov * M_PI/180;
        float half_height = tan(theta/2);
        float half_width = aspect * half_height;
        lower_left_corner = vec3<float>(-half_width, -half_height, -1.0);
        horizontal = vec3<float>(2 * half_width, 0.0, 0.0);
        vertical = vec3<float>(0.0, 2 * half_height, 0.0);
        origin = vec3<float>(0.0, 0.0, 0.0);

        /*
        lower_left_corner = vec3<float>(-2.0, -1.0, -1.0);
        horizontal = vec3<float>(4.0, 0.0, 0.0);
        vertical = vec3<float>(0.0, 2.0, 0.0);
        origin = vec3<float>(0.0, 0.0, 0.0);
        */
    }
    ray<float> GetRay(float u, float v)
    {
        return ray<float>(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }

    vec3<float> origin;
    vec3<float> lower_left_corner;
    vec3<float> horizontal;
    vec3<float> vertical;
};

vec3<float> Color(const ray<float>& r, Geometry *s);


#endif //PATH_TRACER_CAMERA_H
