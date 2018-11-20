//
// Created by Aleksi Hämäläinen on 14/11/2018.
//

#include <hitable/hitable.h>
#include "camera/camera.h"
//#include "ray/ray.h"


vec3<float> color(const ray<float>& r, hitable *world)
{
    hit_record rec;

    if(world->hit(r, 0.000001, MAXFLOAT, rec)){
        vec3<float> target = rec.point + rec.normal + random_in_unit_sphere();
        return (float)0.5*color( ray<float>( rec.point, target-rec.point),world);
    }else{
        vec3<float> unit_direction = r.Direction().unit();
        float t = 0.5*(unit_direction[1]+1.0);
        return ((float)1.0-t)*vec3<float>(1.0,1.0,1.0) + t*vec3<float>(0.5,0.7,1.0);
    }

}