//
// Created by Jan Lundström on 20/11/2018.
//

#ifndef PATH_TRACER_MATERIAL_H
#define PATH_TRACER_MATERIAL_H

#include "geometry/geometry.h"
#include <vector/vec3.h>
#include <ray/ray.h>
#include <texture/texture.h>

class Material {
public:
    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const = 0;
};


class Lambertian : public Material {
public:
    Lambertian(std::shared_ptr<Texture> a) : albedo(a) {}

    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const;

private:
    // The proportion of the total light striking the surface of an object which is reflected from that surface.
    std::shared_ptr<Texture> albedo;
    vec3<float> Random_in_unit_sphere() const;
};


class Metal : public Material {

public:
    Metal(std::shared_ptr<Texture> a) : albedo(a) {}

    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const;

private:
    // The proportion of the total light striking the surface of an object which is reflected from that surface.
    std::shared_ptr<Texture> albedo;
};

vec3<float> Reflect(const vec3<float>& v, const vec3<float>& n);


#endif //PATH_TRACER_MATERIAL_H
