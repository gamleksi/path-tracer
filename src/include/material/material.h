//
// Created by Jan Lundström on 20/11/2018.
//

#ifndef PATH_TRACER_MATERIAL_H
#define PATH_TRACER_MATERIAL_H

#include "geometry/geometry.h"
#include <vector/vec3.h>
#include <ray/ray.h>

 class Material {
 public:
    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const = 0;
    virtual vec3<float> GetAlbedo()const = 0;
};


class Lambertian : public Material {
public:
    Lambertian(const vec3<float>& a) : albedo_(a) {}

    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const;
    virtual vec3<float> GetAlbedo()const{return albedo_;}
private:
    // The proportion of the total light striking the surface of an object which is reflected from that surface.
    vec3<float> albedo_;
    vec3<float> Random_in_unit_sphere() const; //does this need to be in private?
};


class Metal : public Material {
public:
    Metal(const vec3<float>& a) : albedo_(a) {}

    virtual bool Scatter(const ray<float>& r_in, const Hit_record& rec, vec3<float>& attenuation, ray<float>& scattered) const;
    virtual vec3<float> GetAlbedo() const {return albedo_;}

private:
    // The proportion of the total light striking the surface of an object which is reflected from that surface.
    vec3<float> albedo_;
};

vec3<float> Reflect(const vec3<float>& v, const vec3<float>& n);


#endif //PATH_TRACER_MATERIAL_H
