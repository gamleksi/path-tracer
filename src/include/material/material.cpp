//
// Created by Jan Lundström on 20/11/2018.
//

#include "material.h"


vec3<float> RandomInUnitSphere() {

    vec3<float> p;
    do {
        p = (float) 2.0 * vec3<float>((float) drand48(), (float) drand48(), (float) drand48()) - vec3<float>(1, 1, 1);
    } while (p.Squared_length() >= (float) 1.0);
    return p;
}

vec3<float> Reflect(const vec3<float> &v, const vec3<float> &n) {
    return v - 2 * Dot(v, n) * n;
}

bool Lambertian::Scatter(const ray<float> &r_in, const HitRecord& rec, ScatterInfo& srec, float& pdf) const {
    srec.isSpecular = false;
    srec.attenuation = albedo->Value(rec.u, rec.v, rec.point);
    srec.pdf_ptr = std::make_shared<CosinePdf>(rec.normal);
    return true;
}

float Lambertian::ScatteringPdf(const ray<float> &r_in, const HitRecord &rec, const ray<float> &scattered) const {
    float cosine = Dot(rec.normal, (scattered.Direction()).Turn_unit());
    if (cosine < 0)
        return 0;
    return cosine / M_PI;
}

bool Metal::Scatter(const ray<float>& r_in, const HitRecord& hrec, ScatterInfo& srec) const {
    vec3<float> reflected = Reflect((r_in.Direction().Turn_unit()), hrec.normal);
    srec.specularRay = ray<float>(hrec.point, reflected + fuzz*RandomInUnitSphere());
    srec.attenuation = albedo;
    srec.isSpecular = true;
    srec.pdf_ptr = 0;
    return true;
}
bool DiffuseLight::Scatter(const ray<float> &r_in, const HitRecord &rec, vec3<float> &attenuation,
                           ray<float> &scattered) const {
    return false;
}

vec3<float>DiffuseLight::Emitted(const ray<float>& r_in, const HitRecord& rec, float u, float v, const vec3<float>& p) const {
    if (Dot(rec.normal, r_in.Direction()) < 0.0)
        return emit->Value(u, v, p);
    else
        return vec3<float>(0,0,0);
}

bool Dielectric::Refract(const vec3<float> &v, const vec3<float> &n, float ni_over_nt, vec3<float> refracted) const {
    vec3<float> uv = v.Unit();
    float dt = Dot(uv, n);
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    } else {
        return false;
    }
}

float Dielectric::Schkick(float cosine, float ref_idx) const {
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}


bool Dielectric::Scatter(const ray<float>& r_in, const HitRecord& hrec, ScatterInfo& srec) const {
    srec.isSpecular = true;
    srec.pdf_ptr = 0;
    srec.attenuation = vec3<float>(1.0, 1.0, 1.0);
    vec3<float> outward_normal;
    vec3<float> reflected = Reflect(r_in.Direction(), hrec.normal);
    vec3<float> refracted;
    float ni_over_nt;
    float reflect_prob;
    float cosine;
    if (Dot(r_in.Direction(), hrec.normal) > 0) {
        outward_normal = -hrec.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * Dot(r_in.Direction(), hrec.normal) / r_in.Direction().Squared_length();
    }
    else {
        outward_normal = hrec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -Dot(r_in.Direction(), hrec.normal) / r_in.Direction().Squared_length();
    }
    if (Refract(r_in.Direction(), outward_normal, ni_over_nt, refracted)) {
        reflect_prob = Schkick(cosine, ref_idx);
    }
    else {
        reflect_prob = 1.0;
    }
    if (drand48() < reflect_prob) {
        srec.specularRay = ray<float>(hrec.point, reflected);
    }
    else {
        srec.specularRay = ray<float>(hrec.point, refracted);
    }
    return true;
}




