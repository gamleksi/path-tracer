//
// Created by Jan Lundström on 2018-12-11.
//

#ifndef PATH_TRACER_PDF_H
#define PATH_TRACER_PDF_H

#include <vector/vec3.h>
#include <pdf/onb.h>


inline vec3<float> RandomCosineDirection() {
    float r1 = drand48();
    float r2 = drand48();
    float z = sqrt(1 - r2);
    float phi = 2 * M_PI * r1;
    float x = cos(phi) * 2 * sqrt(r2);
    float y = sin(phi) * 2 * sqrt(r2);
    return vec3<float>(x, y, z);
}

inline vec3<float> RandomToSphere(float radius, float distance_squared) {
    float r1 = drand48();
    float r2 = drand48();
    float z = 1 + r2 * (sqrt(1 - radius * radius / distance_squared) - 1);
    float phi = 2 * M_PI * r1;
    float x = cos(phi) * sqrt(1 - z * z);
    float y = sin(phi) * sqrt(1 - z * z);
    return vec3<float>(x, y, z);
}


class Pdf {
public:
    virtual float Value(const vec3<float> &direction) const = 0;

    virtual vec3<float> Generate() const = 0;

    ~Pdf() {}
};


class CosinePdf : public Pdf {
public:
    CosinePdf(const vec3<float> &w) { uvw.Build_from_w(w); }

    virtual float Value(const vec3<float> &direction) const {
        float cosine = Dot((direction), uvw.w().Turn_unit());
        if (cosine > 0)
            return cosine / M_PI;
        else
            return 0;
    }

    virtual vec3<float>

    Generate() const {
        return uvw.Local(RandomCosineDirection());
    }

    Onb uvw;
};

class HitablePdf : public Pdf {
public:
    HitablePdf(std::shared_ptr<Geometry> p, const vec3<float> &origin) : ptr(p), o(origin) {}

    virtual float Value(const vec3<float> &direction) const {
        return ptr->PdfValue(o, direction);
    }

    virtual vec3<float> Generate() const {
        return ptr->Random(o);
    }

    vec3<float> o;
    std::shared_ptr<Geometry> ptr;
};

class MixturePdf : public Pdf {
public:
    MixturePdf(std::shared_ptr<Pdf> p0, std::shared_ptr<Pdf> p1) {
        p[0] = p0;
        p[1] = p1;
    }

    virtual float Value(const vec3<float> &direction) const {
        return 0.5 * p[0]->Value(direction) + 0.5 * p[1]->Value(direction);
    }

    virtual vec3<float> Generate() const {
        if (drand48() < 0.5)
            return p[0]->Generate();
        else
            return p[1]->Generate();
    }

    std::shared_ptr<Pdf> p[2];
};


#endif //PATH_TRACER_PDF_H
