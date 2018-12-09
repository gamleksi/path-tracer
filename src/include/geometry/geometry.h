#include <utility>
#include <algorithm>
#include <iostream>

//
// Created by Jesse Miettinen on 14/11/2018.
//

#ifndef PATH_TRACER_GEOMETRY_H
#define PATH_TRACER_GEOMETRY_H

#include <vector>
#include "vector/vec3.h"
#include "ray/ray.h"
#include "intersection/bounding_box.h"

class Material;

struct Hit_record{ // TODO Fix the name
  float time;
  vec3<float> point;
  vec3<float> normal;
  std::shared_ptr<Material> mat_ptr;
};


class Geometry {
 public:
 virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const = 0;
 virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const = 0;
 virtual int NumberOfObjects() const=0;
};


class Sphere : public Geometry{
  //RayHits algorithm by Peter Shirley, from Ray Tracing in One Weekend, version 1.55
 public:

  Sphere(vec3<float> position, float radius, std::shared_ptr<Material> mat);

  ~Sphere() { };
  float GetRadius() const {
      return radius_;
  }

  vec3<float> GetPosition() const { return position_; };


  virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;

  virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;

  virtual int NumberOfObjects() const;

 private:
  //radius here
  float radius_;
  std::shared_ptr<Material> material_;
  vec3<float> position_;
};

class Geomlist : public Geometry{
 public:

  Geomlist(){}

  Geomlist(std::vector<std::shared_ptr<Geometry>>& object_list)
  : list_size_((int)object_list.size()), list_(object_list) {}

 virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;

 virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
 virtual int NumberOfObjects() const;

 private:
  std::vector<std::shared_ptr<Geometry>> list_;
  int list_size_;

};


class BoundingVolumeNode : public Geometry {

 public:
  BoundingVolumeNode(std::vector<std::shared_ptr<Geometry>>& object_list,
      float t0, float t1, int depth=0);

  BoundingVolumeNode(){}

  virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;

  virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
  virtual int NumberOfObjects() const;
  int NumberOfLeftObjects() const;
  int NumberOfRightObjects() const;

 private:
  std::shared_ptr<Geometry> left_;
  std::shared_ptr<Geometry> right_;
  BoundingBox bounding_box_;

};

bool BBXCompare(const std::shared_ptr<Geometry>& a, const std::shared_ptr<Geometry>& b);
bool BBYCompare(const std::shared_ptr<Geometry>& a, const std::shared_ptr<Geometry>& b);
bool BBZCompare(const std::shared_ptr<Geometry>& a, const std::shared_ptr<Geometry>& b);

void ObjectListSort(std::vector<std::shared_ptr<Geometry>>& object_list, int depth);

#endif //PATH_TRACER_GEOMETRY_H

