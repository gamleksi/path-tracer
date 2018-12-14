//
// Created by Jan Lundström on 20/11/2018.
//

#ifndef PATH_TRACER_MATERIAL_H
#define PATH_TRACER_MATERIAL_H

#include <memory>
#include "geometry/geometry.h"
#include <vector/vec3.h>
#include <ray/ray.h>
#include <texture/texture.h>


/*
 * Abstract class for materials. Materials have 2 base methods "scatter" and "emitted".
 */
class Material {
public:
    /*
     * Different materials scatter light differently
     */
    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const = 0;

    /*
     * Some materials can emit light
     */
    virtual vec3<float> Emitted(float u, float v, const vec3<float>& p) const
    { return vec3<float>(0,0,0); }
};


/*
 * Basic lambertian material represents ideal matte material.
 */
class Lambertian : public Material {
public:
    Lambertian(std::shared_ptr<Texture> a) : albedo(a) {}

    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const;

private:
    // The proportion of the total light striking the surface of an object which is reflected from that surface.
    std::shared_ptr<Texture> albedo;
};



/*
 * Metal material, if fuzz is close to 0 acts as mirror. More fuzz => less sharp reflection
 */
class Metal : public Material {

public:
    //Metal(std::shared_ptr<Texture> a, float f) : albedo(a) { if (f<1) fuzz = f; else fuzz = 1;}
    Metal(vec3<float> a, float f) : albedo(a) { if (f<1) fuzz = f; else fuzz = 1;}

    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const;

private:
    // The proportion of the total light striking the surface of an object which is reflected from that surface.
    vec3<float> albedo;
    // Defines how clearly metallic objects reflect light
    float fuzz;
};


/*
 * DiffuseLight acts as light source
 */
class DiffuseLight : public Material {
public:
    DiffuseLight(std::shared_ptr<Texture> a) : emit(a) {}
    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const;
    virtual vec3<float> Emitted(float u, float v, const vec3<float>& p) const;
private:
    std::shared_ptr<Texture> emit;
};


/*
 * Helping function for Dielectric
 */
vec3<float> Reflect(const vec3<float>& v, const vec3<float>& n);

/*
 * Dielectric is glass like material which reflects and refracts rays.
 */
class Dielectric : public Material {
public:
    Dielectric(float ri) : ref_idx(ri) {}
    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const;

private:
    bool Refract(const vec3<float>& v, const vec3<float>& n, float ni_over_nt, vec3<float> refracted) const;

    // Christophe Schlick polynimial approx ( https://en.wikipedia.org/wiki/Schlick%27s_approximation )
    float Schkick(float cosine, float ref_idx) const;

    float ref_idx;
};



#endif //PATH_TRACER_MATERIAL_H

