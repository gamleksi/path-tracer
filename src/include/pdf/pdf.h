//
// Created by Jan Lundström on 2018-12-11.
//

#ifndef PATH_TRACER_PDF_H
#define PATH_TRACER_PDF_H

#include <vector/vec3.h>
#include <geometry/geometry.h>
#include <pdf/onb.h>


inline vec3<float> Random_cosine_direction() {
    float r1 = drand48();
    float r2 = drand48();
    float z = sqrt(1 - r2);
    float phi = 2 * M_PI * r1;
    float x = cos(phi) * 2 * sqrt(r2);
    float y = sin(phi) * 2 * sqrt(r2);
    return vec3<float>(x, y, z);
}

inline vec3<float> Random_to_sphere(float radius, float distance_squared) {
    float r1 = drand48();
    float r2 = drand48();
    float z = 1 + r2 * (sqrt(1 - radius * radius / distance_squared) - 1);
    float phi = 2 * M_PI * r1;
    float x = cos(phi) * sqrt(1 - z * z);
    float y = sin(phi) * sqrt(1 - z * z);
    return vec3<float>(x, y, z);
}


vec3<float> Random_in_unit_sphere() {
    vec3<float> p;
    do {
        p = (float) 2.0 * vec3<float>(drand48(), drand48(), drand48()) - vec3<float>(1, 1, 1);
    } while (Dot(p, p) >= 1.0);
    return p;
}


class pdf {
public:
    virtual float value(const vec3<float> &direction) const = 0;

    virtual vec3<float> generate() const = 0;

    ~pdf() {}
};


class Cosine_pdf : public pdf {
public:
    Cosine_pdf(const vec3<float> &w) { uvw.Build_from_w(w); }

    virtual float Value(const vec3<float> &direction) const {
        float cosine = Dot((direction), uvw.w().Turn_unit());
        if (cosine > 0)
            return cosine / M_PI;
        else
            return 0;
    }

    virtual vec3<float>

    Generate() const {
        return uvw.Local(Random_cosine_direction());
    }

    Onb uvw;
};

class Hitable_pdf : public pdf {
public:
    Hitable_pdf(std::shared_ptr<Geometry> p, const vec3<float> &origin) : ptr(p), o(origin) {}

    virtual float Value(const vec3<float> &direction) const {
        return ptr->Pdf_value(o, direction);
    }

    virtual vec3<float> generate() const {
        return ptr->Random(o);
    }

    vec3<float> o;
    std::shared_ptr<Geometry> ptr;
};

class Mixture_pdf : public pdf {
public:
    Mixture_pdf(std::shared_ptr<pdf> p0, std::shared_ptr<pdf> p1) {
        p[0] = p0;
        p[1] = p1;
    }

    virtual float Value(const vec3<float> &direction) const {
        return 0.5 * p[0]->value(direction) + 0.5 * p[1]->value(direction);
    }

    virtual vec3<float> generate() const {
        if (drand48() < 0.5)
            return p[0]->generate();
        else
            return p[1]->generate();
    }

    std::shared_ptr<pdf> p[2];
};


#endif //PATH_TRACER_PDF_H
