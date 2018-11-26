//
// Created by Jesse Miettinen on 14/11/2018.
//

#ifndef PATH_TRACER_GEOMETRY_H
#define PATH_TRACER_GEOMETRY_H

#include "vector/vec3.h"
#include "ray/ray.h"

class Material;

struct hit_record {
    float time;
    vec3<float> point;
    vec3<float> normal;
    Material *mat_ptr;
};



class Geometry {
public:
    Geometry(vec3<float> pos, Material* mat) : material_(mat), position_(pos) {}
    Geometry(){};
    //destructor virtual
    virtual ~Geometry() { };

    vec3<float> GetPosition() const{
        return position_;
    }
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, hit_record& rec) const = 0;


private:
    Material* material_;
    vec3<float> position_;
};


class Sphere : public Geometry{
    //RayHits algorithm by Peter Shirley, from Ray Tracing in One Weekend, version 1.55
public:
    Sphere(vec3<float> pos, float radius, Material* mat) : Geometry(pos, mat), radius_(radius) { }
    Sphere(){};
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
    Geomlist(){};
    Geomlist(Geometry **g, int n){list_ = g; list_size_ = n;}
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, hit_record& rec) const;
    Geometry **list_;
    int list_size_;

};


#endif //PATH_TRACER_GEOMETRY_H
