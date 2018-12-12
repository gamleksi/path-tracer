//
// Created by Jan Lundström on 20/11/2018.
//

#ifndef PATH_TRACER_MATERIAL_H
#define PATH_TRACER_MATERIAL_H

#include "geometry/geometry.h"
#include <vector/vec3.h>
#include <ray/ray.h>
#include <texture/texture.h>
#include <pdf/pdf.h>



struct ScatterInfo {
    ray<float> specularRay;
    bool isSpecular;
    vec3<float> attenuation;
    std::shared_ptr<Pdf> pdf_ptr;
};

class Material {
public:
    virtual bool Scatter(const ray<float>& r_in, const HitRecord& rec, ScatterInfo& srec) const {
        return false;}

    virtual float ScatteringPdf(const ray<float>& r_in, const HitRecord& rec, const ray<float>& scattered) const {
        return false;}

    virtual vec3<float> Emitted(const ray<float> &r_in, const HitRecord &rec, float u, float v, const vec3<float> &p) const {
        return vec3<float>(0, 0, 0);
    }
};


class Lambertian : public Material {
public:
    Lambertian(std::shared_ptr<Texture> a) : albedo(a) {}


    virtual float ScatteringPdf(const ray<float>& r_in, const HitRecord& rec, const ray<float>& scattered) const;

    virtual bool Scatter(const ray<float> &r_in, const HitRecord& rec, ScatterInfo& srec, float& pdf) const;

private:
    // The proportion of the total light striking the surface of an object which is reflected from that surface.
    std::shared_ptr<Texture> albedo;
};


class Metal : public Material {

public:
    Metal(const vec3<float>& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }

    virtual bool Scatter(const ray<float>& r_in, const HitRecord& hrec, ScatterInfo& srec) const;

private:
    // The proportion of the total light striking the surface of an object which is reflected from that surface.
    vec3<float> albedo;
    // Defines how clearly metallic objects reflect light
    float fuzz;
};


class DiffuseLight : public Material {
public:
    DiffuseLight(std::shared_ptr<Texture> a) : emit(a) {}

    virtual vec3<float>
    Emitted(const ray<float> &r_in, const HitRecord &rec, float u, float v, const vec3<float> &p) const;

private:
    std::shared_ptr<Texture> emit;
};

vec3<float> Reflect(const vec3<float> &v, const vec3<float> &n);

class Dielectric : public Material {
public:
    Dielectric(float ri) : ref_idx(ri) {}

    virtual bool
    Scatter(const ray<float>& r_in, const HitRecord& hrec, ScatterInfo& srec) const;

private:
    bool Refract(const vec3<float> &v, const vec3<float> &n, float ni_over_nt, vec3<float> refracted) const;

    // Christophe Schlick polynimial approx
    float Schkick(float cosine, float ref_idx) const;

    float ref_idx;
};


#endif //PATH_TRACER_MATERIAL_H

