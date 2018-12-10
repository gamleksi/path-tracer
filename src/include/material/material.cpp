//
// Created by Jan Lundström on 20/11/2018.
//

#include "material.h"


bool Lambertian::Scatter(
        const ray<float> &r_in, const Hit_record &rec,
        vec3<float> &attenuation, ray<float> &scattered) const {

    vec3<float> target = rec.point + rec.normal + Random_in_unit_sphere();
    scattered = ray<float>(rec.point, target - rec.point);
    attenuation = albedo->Value(0, 0, rec.point);

    return true;
}

vec3<float> Lambertian::Random_in_unit_sphere() const {

    vec3<float> p;
    do {
        p = (float) 2.0 * vec3<float>((float) drand48(), (float) drand48(), (float) drand48()) - vec3<float>(1, 1, 1);
    } while (p.Squared_length() >= (float) 1.0);
    return p;
}

vec3<float> Reflect(const vec3<float> &v, const vec3<float> &n) {
    return v - 2 * Dot(v, n) * n;
}

bool Metal::Scatter(const ray<float> &r_in, const Hit_record &rec,
                    vec3<float> &attenuation, ray<float> &scattered) const {
    vec3<float> reflected = Reflect(r_in.Direction().Turn_unit(), rec.normal);
    scattered = ray<float>(rec.point, reflected);
    attenuation = albedo->Value(0, 0, rec.point);
    return (Dot(scattered.Direction(), rec.normal) > 0);
}

bool DiffuseLight::Scatter(const ray<float> &r_in, const Hit_record &rec, vec3<float> &attenuation,
                           ray<float> &scattered) const {
    return false;
}

vec3<float> DiffuseLight::emitted(float u, float v, const vec3<float> &p) const {
    return emit->Value(u, v, p);
}

bool Dielectric::Refract(const vec3<float>& v, const vec3<float>& n, float ni_over_nt, vec3<float> refracted) const {
    vec3<float> uv = v.Unit();
    float dt = Dot(uv,n);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant > 0) {
        refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
        return true;
    } else {
        return false;
    }
}

float Dielectric::Schkick(float cosine, float ref_idx) const {
    float r0 = (1-ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1-r0)*pow((1-cosine),5);
}


bool Dielectric::Scatter(const ray<float> &r_in, const Hit_record &rec, vec3<float>& attenuation, ray<float>& scattered) const {
    vec3<float> outward_normal;
    vec3<float> reflected = Reflect(r_in.Direction(), rec.normal);
    float ni_over_nt;
    attenuation = vec3<float>(1.0,1.0,1.0);
    vec3<float> refracted;
    float reflect_prob;
    float cosine;
    if (Dot(r_in.Direction(), rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_over_nt = this->ref_idx;
        cosine = ref_idx * Dot(r_in.Direction(), rec.normal) / sqrt(r_in.Direction().Squared_length());
    } else {
        outward_normal = rec.normal;
        ni_over_nt = 1.0 / this->ref_idx;
        cosine = -Dot(r_in.Direction(), rec.normal) / sqrt(r_in.Direction().Squared_length());
    }
    if (Refract(r_in.Direction(), outward_normal, ni_over_nt, refracted)) {
        reflect_prob = Schkick(cosine,ref_idx);
    } else {
        reflect_prob = 1.0;
    }
    if (drand48() < reflect_prob) {
        scattered = ray<float>(rec.point, reflected);
    } else {
        scattered = ray<float>(rec.point, reflected);
    }
    return true;

}




