//
// Created by Jan Lundström on 20/11/2018.
//

#ifndef PATH_TRACER_MATERIAL_H
#define PATH_TRACER_MATERIAL_H


#include <vector/vec3.h>
#include <ray/ray.h>
#include <geometry/geometry.h>


class Material {
public:
    virtual bool scatter(const ray<float> &r_in, const hit_record &rec, vec3<float> &attenuation, ray<float> &scattered) const = 0;

};


class Lambertian : public Material {
public:
    Lambertian(const vec3<float> &a) : albedo(a) {}

    vec3<float> random_in_unit_sphere() const {
        vec3<float> p;
        do {
            p = (float) 2.0*vec3<float>( (float) drand48(), (float) drand48(), (float) drand48()) - vec3<float>(1,1,1);
        } while (p.squared_length() >= (float) 1.0);
        return p;
    }


    bool scatter(const ray<float> &r_in, const hit_record &rec, vec3<float> &attenuation, ray<float> &scattered) const {
        vec3<float> target = rec.point + rec.normal + random_in_unit_sphere();
        scattered = ray<float>(rec.point, target - rec.point);
        attenuation = albedo;
        return true;
    }

    vec3<float> albedo;
};


//class Metal : public Material {
//public:
//    Metal(const vec3<float> &a) : albedo(a) {}
//
//    vec3<float> reflect(const vec3<float>& v, const vec3<float>& n);
//    bool scatter(const ray<float> &r_in, const hit_record &rec, vec3<float> &attenuation, ray<float> &scattered) const;
//
//    vec3<float> albedo;
//};


#endif //PATH_TRACER_MATERIAL_H
