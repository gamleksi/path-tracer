//
// Created by Jan Lundström on 2018-12-12.
//

#ifndef PATH_TRACER_BOX_H
#define PATH_TRACER_BOX_H

#include "geometry/geometry.h"
#include "geometry/geomlist.h"

class Box : public Geometry {
public:
    Box() {}

    Box(const vec3<float> &p0, const vec3<float> &p1, std::shared_ptr<Material> mat);

    ~Box() {};

    virtual bool RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const;

    virtual bool GetBoundingBox(float t0, float t1, BoundingBox &box) const;

    virtual int NumberOfObjects() const;

private:
    vec3<float> pmin_, pmax_;
    std::shared_ptr<Geomlist> list_ptr_;
};


#endif //PATH_TRACER_BOX_H
