//
// Created by Aleksi Hämäläinen on 14/12/2018.
//

#ifndef PATH_TRACER_GEOMLIST_H
#define PATH_TRACER_GEOMLIST_H

#include "geometry/geometry.h"

class Geomlist : public Geometry {
 public:

    Geomlist(){}

    Geomlist(std::vector<std::shared_ptr<Geometry>>& object_list)
    : list_size_((int)object_list.size()), list_(object_list) {}

    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, HitRecord& rec) const;

    virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
    virtual int NumberOfObjects() const;

 private:
    std::vector<std::shared_ptr<Geometry>> list_;
    int list_size_;

};

#endif //PATH_TRACER_GEOMLIST_H
