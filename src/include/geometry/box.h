//
// Created by Aleksi Hämäläinen on 14/12/2018.
//

#ifndef PATH_TRACER_BOX_H
#define PATH_TRACER_BOX_H

#include "geometry/geometry.h"
#include "geometry/geomlist.h"

class Box : public Geometry {
public:
    Box() { }
    Box(const vec3<float>& p0, const vec3<float>& p1, std::shared_ptr<Material> mat);
    ~Box() { };
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
    virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
    virtual int NumberOfObjects() const;
private:
    vec3<float> pmin_, pmax_;
    std::shared_ptr<Geomlist> list_ptr_;
};

class XyRect : public Geometry{
public:
    XyRect(float x0, float x1, float y0, float y1, float k, std::shared_ptr<Material> mat);

    ~XyRect() { };
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
    virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
    virtual int NumberOfObjects() const;
private:
    float x0_, x1_, y0_, y1_, k_;
    std::shared_ptr<Material> material_;
};

class XzRect : public Geometry{
public:
    XzRect(float x0, float x1, float z0, float z1, float k, std::shared_ptr<Material> mat);

    ~XzRect() { };
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
    virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
    virtual int NumberOfObjects() const;
private:
    float x0_, x1_, z0_, z1_, k_;
    std::shared_ptr<Material> material_;
};

class YzRect : public Geometry{
public:
    YzRect(float y0, float y1, float z0, float z1, float k, std::shared_ptr<Material> mat);

    ~YzRect() { };
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
    virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
    virtual int NumberOfObjects() const;
private:
    float y0_, y1_, z0_, z1_, k_;
    std::shared_ptr<Material> material_;
};

class FlipNormals : public Geometry{
public:
    FlipNormals(std::shared_ptr<Geometry> p) : ptr_(p) { }
    ~FlipNormals() { }
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const {
        if (ptr_->RayHits(r, t_min, t_max, rec)) {
            rec.normal = -rec.normal;
            return true;
        } else {
            return false;
        }
    }
    virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const{
        return ptr_->GetBoundingBox(t0, t1, box);
    }
    virtual int NumberOfObjects() const { return 1; }
private:
    std::shared_ptr<Geometry> ptr_;
};

#endif //PATH_TRACER_BOX_H
