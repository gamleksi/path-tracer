//
// Created by Jan Lundström on 2018-12-12.
//

#include "box.h"


bool Box::RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const {
    return list_ptr_->RayHits(r, t_min, t_max, rec);
}

bool Box::GetBoundingBox(float t0, float t1, BoundingBox &box) const {
    box = BoundingBox(pmin_, pmax_);
    return true;
}

Box::Box(const vec3<float> &p0, const vec3<float> &p1, std::shared_ptr<Material> mat) {
    pmin_ = p0;
    pmax_ = p1;

    std::vector<std::shared_ptr<Geometry>> rect_list(6);

    rect_list[0] = std::make_shared<XyRect>(p0.X(), p1.X(), p0.Y(), p1.Y(), p1.Z(), mat);
    rect_list[1] = std::make_shared<FlipNormals>(std::make_shared<XyRect>(p0.X(), p1.X(), p0.Y(), p1.Y(), p0.Z(), mat));
    rect_list[2] = std::make_shared<XzRect>(p0.X(), p1.X(), p0.Z(), p1.Z(), p1.Y(), mat);
    rect_list[3] = std::make_shared<FlipNormals>(std::make_shared<XzRect>(p0.X(), p1.X(), p0.Z(), p1.Z(), p0.Y(), mat));
    rect_list[4] = std::make_shared<YzRect>(p0.Y(), p1.Y(), p0.Z(), p1.Z(), p1.X(), mat);
    rect_list[5] = std::make_shared<FlipNormals>(std::make_shared<YzRect>(p0.Y(), p1.Y(), p0.Z(), p1.Z(), p0.X(), mat));
    list_ptr_ = std::make_shared<Geomlist>(rect_list);
}

int Box::NumberOfObjects() const {
    return 1;
}

