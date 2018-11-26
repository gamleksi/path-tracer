//
// Created by Jesse Miettinen on 14/11/2018.
//

#ifndef PATH_TRACER_GEOMETRY_H
#define PATH_TRACER_GEOMETRY_H

#include "vector/vec3.h"
#include "ray/ray.h"

class Material;

struct Hit_record{
  float time;
  vec3<float> point;
  vec3<float> normal;
  Material* mat_ptr;
};


class Geometry {
 public:
 virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const = 0;
};

class Sphere : public Geometry{
  //RayHits algorithm by Peter Shirley, from Ray Tracing in One Weekend, version 1.55
 public:


  Sphere(vec3<float> position, float radius, Material* mat)
  : Geometry(), radius_(radius), position_(position), material_(mat) { }
  //get radius and ray hits Sphere
  ~Sphere() { };
  float GetRadius() const {
      return radius_;
  }

  virtual vec3<float> GetPosition() const { return position_; };

  virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
  //discriminant stuff
 private:
  //radius here
  float radius_;
  Material* material_;
  vec3<float> position_;
};

class Geomlist : public Geometry{
 public:
  Geomlist(){}
  Geomlist(Geometry **g, int n){list_ = g; list_size_ = n;}
  virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
  Geometry **list_;
  int list_size_;

};

#endif //PATH_TRACER_GEOMETRY_H

