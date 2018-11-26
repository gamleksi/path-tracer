//
// Created by Jan Lundström on 20/11/2018.
//

#ifndef PATH_TRACER_MATERIAL_H
#define PATH_TRACER_MATERIAL_H

#include "geometry/geometry.h"
#include "hitable/hitable.h"
#include <vector/vec3.h>
#include <ray/ray.h>

class Material {
public:
    virtual bool scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const = 0;
};


class Lambertian : public Material {
public:
    Lambertian(const vec3<float>& a) : albedo(a) {}

    virtual bool scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const;

    vec3<float> albedo;
    vec3<float> random_in_unit_sphere() const;
};

vec3<float> reflect(const vec3<float>& v, const vec3<float>& n);

class Metal : public Material {
public:
    Metal(const vec3<float>& a) : albedo(a) {}

    virtual bool scatter(
        const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation,
        ray<float>& scattered
        ) const;

    vec3<float> albedo;
};

#endif //PATH_TRACER_MATERIAL_H
