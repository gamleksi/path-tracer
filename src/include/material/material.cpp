//
// Created by Jan Lundström on 20/11/2018.
//

#include "material.h"


vec3<float> random_in_unit_sphere() {
    vec3<float> p;
    do {
        p = (float) 2.0*vec3<float>( (float) drand48(), (float) drand48(), (float) drand48()) - vec3<float>(1,1,1);
    } while (p.squared_length() >= (float) 1.0);
    return p;
}

//bool Lambertian::scatter(const ray<float> &r_in, const hit_record &rec, vec3<float> &attenuation, ray<float> &scattered) const {
//    vec3<float> target = rec.point + rec.normal + random_in_unit_sphere();
//    scattered = ray<float>(rec.point, target - rec.point);
//    attenuation = albedo;
//    return true;
//}




//
//vec3<float> Metal::reflect(const vec3<float>& v, const vec3<float>& n) const {
//    return v - 2*dot(v,n)*n;
//}
//
//bool Metal::scatter(const ray<float> &r_in, const hit_record &rec, vec3<float> &attenuation, ray<float> &scattered) const {
//    vec3<float> reflected = this->reflect(r_in.direction().turn_unit(), rec.normal);
//    scattered = ray<float>(rec.point, reflected);
//    attenuation = albedo;
//    return (dot(scattered.direction(), rec.normal) > 0);
//}