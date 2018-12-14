//
// Created by Jan Lundström on 20/11/2018.
//

#ifndef PATH_TRACER_MATERIAL_H
#define PATH_TRACER_MATERIAL_H

#include <memory.h>
#include "geometry/geometry.h"
#include <vector/vec3.h>
#include <ray/ray.h>
#include <texture/texture.h>

class Material {
public:
    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const = 0;
    virtual vec3<float> Emitted(float u, float v, const vec3<float>& p) const
    { return vec3<float>(0,0,0); }
};


class Lambertian : public Material {
public:
    Lambertian(std::shared_ptr<Texture> a) : albedo(a) {}

    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const;

private:
    // The proportion of the total light striking the surface of an object which is reflected from that surface.
    std::shared_ptr<Texture> albedo;
};


class Metal : public Material {

public:
    Metal(std::shared_ptr<Texture> a, float f) : albedo(a) { if (f<1) fuzz = f; else fuzz = 1;}

    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const;

private:
    // The proportion of the total light striking the surface of an object which is reflected from that surface.
    std::shared_ptr<Texture> albedo;
    // Defines how clearly metallic objects reflect light
    float fuzz;
};

class DiffuseLight : public Material {
public:
    DiffuseLight(std::shared_ptr<Texture> a) : emit(a) {}
    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const;
    virtual vec3<float> Emitted(float u, float v, const vec3<float>& p) const;
private:
    std::shared_ptr<Texture> emit;
};

vec3<float> Reflect(const vec3<float>& v, const vec3<float>& n);

class Dielectric : public Material {
public:
    Dielectric(float ri) : ref_idx(ri) {}
    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const;

private:
    bool Refract(const vec3<float>& v, const vec3<float>& n, float ni_over_nt, vec3<float> refracted) const;

    // Christophe Schlick polynimial approx
    float Schkick(float cosine, float ref_idx) const ;

    float ref_idx;
};



#endif //PATH_TRACER_MATERIAL_H

