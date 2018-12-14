#include <utility>
#include <algorithm>
#include <iostream>

//
// Created by Jesse Miettinen on 14/11/2018.
//

#ifndef PATH_TRACER_GEOMETRY_H
#define PATH_TRACER_GEOMETRY_H

#include <memory>
#include <vector>
#include "vector/vec3.h"
#include "ray/ray.h"
#include "intersection/bounding_box.h"

class Material;

struct HitRecord { // TODO Fix the name
    float time;
    float u;
    float v;
    vec3<float> point;
    vec3<float> normal;
    std::shared_ptr<Material> mat_ptr;
};


class Geometry {
public:
    virtual bool RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const = 0;

    virtual bool GetBoundingBox(float t0, float t1, BoundingBox &box) const = 0;

    virtual int NumberOfObjects() const = 0;

    virtual float PdfValue(const vec3<float> &o, const vec3<float> &v) const {return 0.0;}

    virtual vec3<float> Random(const vec3<float> &o) const {return vec3<float>(1, 0, 0);}
};


class XyRect : public Geometry {
public:
    XyRect(float x0, float x1, float y0, float y1, float k, std::shared_ptr<Material> mat);

    ~XyRect() {};

    virtual bool RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const;

    virtual bool GetBoundingBox(float t0, float t1, BoundingBox &box) const;

    virtual int NumberOfObjects() const;

    virtual vec3<float> Random(const vec3<float> &o) const;

    virtual float  PdfValue(const vec3<float>& o, const vec3<float>& v) const;

private:
    float x0_, x1_, y0_, y1_, k_;
    std::shared_ptr<Material> material_;
};

class XzRect : public Geometry {
public:
    XzRect(float x0, float x1, float z0, float z1, float k, std::shared_ptr<Material> mat);

    ~XzRect() {};

    virtual bool RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const;

    virtual bool GetBoundingBox(float t0, float t1, BoundingBox &box) const;

    virtual int NumberOfObjects() const;

    virtual vec3<float> Random(const vec3<float> &o) const;

    virtual float  PdfValue(const vec3<float>& o, const vec3<float>& v) const;

private:
    float x0_, x1_, z0_, z1_, k_;
    std::shared_ptr<Material> material_;
};

class YzRect : public Geometry {
public:
    YzRect(float y0, float y1, float z0, float z1, float k, std::shared_ptr<Material> mat);

    ~YzRect() {};

    virtual bool RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const;

    virtual bool GetBoundingBox(float t0, float t1, BoundingBox &box) const;

    virtual int NumberOfObjects() const;

    virtual vec3<float> Random(const vec3<float> &o) const;

    virtual float  PdfValue(const vec3<float>& o, const vec3<float>& v) const;

private:
    float y0_, y1_, z0_, z1_, k_;
    std::shared_ptr<Material> material_;
};

class FlipNormals : public Geometry {
public:
    FlipNormals(std::shared_ptr<Geometry> p) : ptr_(p) {}

    ~FlipNormals() {}

    virtual bool RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const {
        if (ptr_->RayHits(r, t_min, t_max, rec)) {
            rec.normal = -rec.normal;
            return true;
        } else {
            return false;
        }
    }

    virtual bool GetBoundingBox(float t0, float t1, BoundingBox &box) const {
        return ptr_->GetBoundingBox(t0, t1, box);
    }

    virtual int NumberOfObjects() const { return 1; }

private:
    std::shared_ptr<Geometry> ptr_;
};

class BoundingVolumeNode : public Geometry {

public:
    BoundingVolumeNode(std::vector<std::shared_ptr<Geometry>> &object_list,
                       float t0, float t1, int depth = 0);

    BoundingVolumeNode() {}

    virtual bool RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const;

    virtual bool GetBoundingBox(float t0, float t1, BoundingBox &box) const;

    virtual int NumberOfObjects() const;

    int NumberOfLeftObjects() const;

    int NumberOfRightObjects() const;

private:
    std::shared_ptr<Geometry> left_;
    std::shared_ptr<Geometry> right_;
    BoundingBox bounding_box_;

};

class Sphere : public Geometry {
public:

    Sphere(vec3<float> position, float radius, std::shared_ptr<Material> mat)
            : Geometry(), radius_(radius), position_(position), material_(std::move(mat)) { }

    ~Sphere() {};

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

class Geomlist : public Geometry {
public:

    Geomlist() {}

    Geomlist(std::vector<std::shared_ptr<Geometry>> &object_list_)
            : list_size((int) object_list_.size()), list(object_list_) {}

    virtual bool RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const;

    virtual bool GetBoundingBox(float t0, float t1, BoundingBox &box) const;

    virtual int NumberOfObjects() const;

    float PdfValue(const vec3<float>& o, const vec3<float>& v) const;

    vec3<float> Random(const vec3<float>& o) const;

private:
    std::vector<std::shared_ptr<Geometry>> list;
    int list_size;

};

bool BBXCompare(const std::shared_ptr<Geometry> &a, const std::shared_ptr<Geometry> &b);

bool BBYCompare(const std::shared_ptr<Geometry> &a, const std::shared_ptr<Geometry> &b);

bool BBZCompare(const std::shared_ptr<Geometry> &a, const std::shared_ptr<Geometry> &b);

void ObjectListSort(std::vector<std::shared_ptr<Geometry>> &object_list, int depth);

#endif //PATH_TRACER_GEOMETRY_H

