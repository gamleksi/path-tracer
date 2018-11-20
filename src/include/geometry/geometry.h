//
// Created by Jesse Miettinen on 14/11/2018.
//

#ifndef PATH_TRACER_GEOMETRY_H
#define PATH_TRACER_GEOMETRY_H

#include <hitable/hitable.h>
#include "vector/vec3.h"
#include "ray/ray.h"

//Leaving this here for future.
//enum Material
//{
//    Matte,
//    Glass,
//    Metal
//};

class Geometry {
public:
    //constructor - change material when ready
    Geometry(vec3<float> position = vec3<float>(1.0,2.0,3.0))
            : position_(position) { }
    //destructor virtual
    virtual ~Geometry() { };

    //some utilities, maybe needed get etc

//    Material GetMaterial() const{
//        return material_;
//   }

    vec3<float> GetPosition() const{
        return position_;
    }
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, hit_record& rec) const = 0;


private:
    //material will be used later.

//    Material material_; // not implemented yet.
    vec3<float> position_;
};


class Sphere : public Geometry{
    //RayHits algorithm by Peter Shirley, from Ray Tracing in One Weekend, version 1.55
public:
    Sphere(vec3<float> position = vec3<float>(0.0,0.0,-1.0), float radius = 0.5)
            : Geometry(position), radius_(radius) { }
    //get radius and ray hits Sphere
    virtual ~Sphere() { };
    float GetRadius() const {
        return radius_;
    }

    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, hit_record& rec) const;
    //discriminant stuff
private:
    //radius here
    float radius_;

};

class Geomlist : public Geometry{
public:
    Geomlist() { }
    Geomlist(Geometry **g, int n){list_ = g; list_size_ = n;}
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, hit_record& rec) const;
    Geometry **list_;
    int list_size_;

};

#endif //PATH_TRACER_GEOMETRY_H
