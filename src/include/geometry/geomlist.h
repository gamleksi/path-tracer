//
// Created by Jan Lundström on 2018-12-12.
//

#ifndef PATH_TRACER_GEOMLIST_H
#define PATH_TRACER_GEOMLIST_H

#include "geometry/geometry.h"
//
//class Geomlist : public Geometry {
//public:
//
//    Geomlist() {}
//
//    Geomlist(std::vector<std::shared_ptr<Geometry>> &object_list_)
//            : list_size((int) object_list_.size()), list(object_list_) {}
//
//    virtual bool RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const;
//
//    virtual bool GetBoundingBox(float t0, float t1, BoundingBox &box) const;
//
//    virtual int NumberOfObjects() const;
//
//    float PdfValue(const vec3<float>& o, const vec3<float>& v) const;
//
//    vec3<float> Random(const vec3<float>& o) const;
//
//private:
//    std::vector<std::shared_ptr<Geometry>> list;
//    int list_size;
//
//};


#endif //PATH_TRACER_GEOMLIST_H
