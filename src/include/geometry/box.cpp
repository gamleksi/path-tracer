//
// Created by Aleksi Hämäläinen on 14/12/2018.
//

#include "box.h"

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

bool Box::RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const {
    return list_ptr_->RayHits(r, t_min, t_max, rec);
}

bool Box::GetBoundingBox(float t0, float t1, BoundingBox &box) const {
    box = BoundingBox(pmin_, pmax_);
    return true;
}

XyRect::XyRect(float x0, float x1, float y0, float y1, float k, std::shared_ptr<Material> mat)
    : x0_(x0), x1_(x1), y0_(y0), y1_(y1), k_(k), material_(std::move(mat)) { }

XzRect::XzRect(float x0, float x1, float z0, float z1, float k, std::shared_ptr<Material> mat)
    : x0_(x0), x1_(x1), z0_(z0), z1_(z1), k_(k), material_(std::move(mat)) { }

YzRect::YzRect(float y0, float y1, float z0, float z1, float k, std::shared_ptr<Material> mat)
    : y0_(y0), y1_(y1), z0_(z0), z1_(z1), k_(k), material_(std::move(mat)) { }

bool XyRect::RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const {
    float t = (k_ - r.Origin().Z()) / r.Direction().Z();
    if (t < t_min || t > t_max){ return false; }
    float x = r.Origin().X() + t * r.Direction().X();
    float y = r.Origin().Y() + t * r.Direction().Y();
    if (x < x0_ || x > x1_ || y < y0_ || y > y1_) { return false; }
    rec.u = (x - x0_) / (x1_ - x0_);
    rec.v = (y - y0_) / (y1_ - y0_);
    rec.time = t;
    rec.mat_ptr = material_;
    rec.point = r.Point(t);
    rec.normal = vec3<float>(0,0,1);
    return true;
}

bool XzRect::RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const {
    float t = (k_ - r.Origin().Y()) / r.Direction().Y();
    if (t < t_min || t > t_max) { return false; }
    float x = r.Origin().X() + t * r.Direction().X();
    float z = r.Origin().Z() + t * r.Direction().Z();
    if (x < x0_ || x > x1_ || z < z0_ || z > z1_) { return false; }
    rec.u = (x - x0_) / (x1_ - x0_);
    rec.v = (z - z0_) / (z1_ - z0_);
    rec.time = t;
    rec.mat_ptr = material_;
    rec.point = r.Point(t);
    rec.normal = vec3<float>(0, 1, 0);
    return true;
}

bool YzRect::RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const {
    float t = (k_ - r.Origin().X()) / r.Direction().X();
    if (t < t_min || t > t_max) { return false; }
    float y = r.Origin().Y() + t * r.Direction().Y();
    float z = r.Origin().Z() + t * r.Direction().Z();
    if (y < y0_ || y > y1_ || z < z0_ || z > z1_) { return false; }
    rec.u = (y - y0_) / (y1_ - y0_);
    rec.v = (z - z0_) / (z1_ - z0_);
    rec.time = t;
    rec.mat_ptr = material_;
    rec.point = r.Point(t);
    rec.normal = vec3<float>(1, 0, 0);
    return true;
}


int XyRect::NumberOfObjects() const {
   return 1;
}

int XzRect::NumberOfObjects() const {
   return 1;
}

int YzRect::NumberOfObjects() const {
   return 1;
}

int Box::NumberOfObjects() const {
   return 1;
}

bool XyRect::GetBoundingBox(float t0, float t1, BoundingBox &box) const {
    box = BoundingBox(vec3<float>(x0_,y0_,k_-0.001), vec3<float>(x1_,y1_,k_+0.001));
    return true;
}

bool XzRect::GetBoundingBox(float t0, float t1, BoundingBox &box) const {
    box = BoundingBox(vec3<float>(x0_,k_-0.0001,z0_), vec3<float>(x1_,k_+0.0001,z1_));
    return true;
}

bool YzRect::GetBoundingBox(float t0, float t1, BoundingBox &box) const {
    box = BoundingBox(vec3<float>(k_-0.0001,y0_,z0_), vec3<float>(k_+0.0001,y1_,z1_));
    return true;
}


