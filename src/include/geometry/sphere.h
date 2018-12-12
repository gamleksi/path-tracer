//
// Created by Jan Lundström on 2018-12-12.
//

#ifndef PATH_TRACER_SPHERE_H
#define PATH_TRACER_SPHERE_H


#include "geometry.h"

class Sphere : public Geometry {
public:

    Sphere(vec3<float> position, float radius, std::shared_ptr<Material> mat);

    ~Sphere() {};

    float GetRadius() const {
        return radius_;
    }

    vec3<float> GetPosition() const { return position_; };

    virtual bool RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const;

    virtual bool GetBoundingBox(float t0, float t1, BoundingBox &box) const;

    virtual int NumberOfObjects() const;

    virtual float PdfValue(const vec3<float> &o, const vec3<float> &v) const;

    virtual vec3<float> Random(const vec3<float> &o) const;

private:
    //radius here
    float radius_;
    std::shared_ptr<Material> material_;
    vec3<float> position_;
};



#endif //PATH_TRACER_SPHERE_H
