//
// Created by Jesse Miettinen on 14/11/2018.
//

#ifndef PATH_TRACER_GEOMETRY_H
#define PATH_TRACER_GEOMETRY_H

#include "vector/vec3.h"
#include "ray/ray.h"


enum Material
{
    Matte,
    Glass,
    Metal
};

struct Hit_record{
    float time;
    vec3<float> point;
    vec3<float> normal;
};


class Geometry {
public:
    //constructor - change material when ready
    Geometry(std::string name = "abc", Material mat = Matte, vec3<float> position = vec3<float>(1.0,2.0,3.0))
            : name_(name), material_(mat), position_(position) { }
    //destructor virtual
    virtual ~Geometry() { };

    //some utilities, maybe needed get etc
    std::string GetName() const{
        return name_; //needs to be a const ref most likely
    }
    Material GetMaterial() const{
        return material_;
    }
    vec3<float> GetPosition() const{
        return position_;
    }
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const = 0;


private:
    //name, material and position vec3
    std::string name_;
    Material material_; // not implemented yet.
    vec3<float> position_;
};


class Sphere : public Geometry{
    //RayHits algorithm by Peter Shirley, from Ray Tracing in One Weekend, version 1.55
public:
    Sphere(std::string name = "abc", Material mat = Matte, vec3<float> position = vec3<float>(0.0,0.0,-1.0), float radius = 0.5)
            : Geometry(name, mat, position), radius_(radius) { }
    //get radius and ray hits Sphere
    virtual ~Sphere() { };
    float GetRadius() const {
        return radius_;
    }

    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
    //discriminant stuff
private:
    //radius here
    float radius_;

};

class Geomlist : public Geometry{
public:
    Geomlist() { }
    Geomlist(Geometry **g, int n){list_ = g; list_size_ = n;}
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
    Geometry **list_;
    int list_size_;

};

#endif //PATH_TRACER_GEOMETRY_H
