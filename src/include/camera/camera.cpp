//
// Created by Aleksi Hämäläinen on 14/11/2018.
//

#include "camera/camera.h"
//#include "ray/ray.h"


vec3<float> Color(const ray<float>& r, Geometry *s)
{
    Hit_record rec;

    if(s->RayHits(r, 0.0, MAXFLOAT, rec)){
        return (float)0.5*vec3<float>(rec.normal[0]+1,rec.normal[1]+1,rec.normal[2]+1);
    }else{
        vec3<float> unit_direction = r.Direction().unit();
        float t = 0.5*(unit_direction[1]+1.0);
        return ((float)1.0-t)*vec3<float>(1.0,1.0,1.0) + t*vec3<float>(0.5,0.7,1.0);
    }

}