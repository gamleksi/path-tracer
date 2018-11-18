//
// Created by Ville Leppälä on 14.11.2018.
//

#ifndef PATH_TRACER_CAMERA_H
#define PATH_TRACER_CAMERA_H

#include "ray/ray.h"

class camera {
public:
    camera()
    {
        lower_left_corner = vec3<float>(-2.0, -1.0, -1.0);
        horizontal = vec3<float>(4.0, 0.0, 0.0);
        vertical = vec3<float> (0.0, 2.0, 0.0);
        origin = vec3<float> (0.0, 0.0, 0.0);
    }
    ray<float> get_ray(float u, float v)
    {
        return ray<float>(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }

    vec3<float> origin;
    vec3<float> lower_left_corner;
    vec3<float> horizontal;
    vec3<float> vertical;
};


#endif //PATH_TRACER_CAMERA_H
