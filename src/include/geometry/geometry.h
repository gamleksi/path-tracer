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

// Used to inform compiler
class Material;

struct HitRecord{
  float time;
  float u;
  float v;
  vec3<float> point;
  vec3<float> normal;
  std::shared_ptr<Material> mat_ptr;
};


/*
 * Geometry abstract class contains different geometries. RayHits function calculates did the ray hit certain geometry.
 * GetBoundingBox is used by bounding volume calculations
 */
class Geometry {
 public:
 virtual bool RayHits(const ray<float>& r, float t_min, float t_max, HitRecord& rec) const = 0;
 virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const = 0;
 virtual int NumberOfObjects() const=0;
};

bool BBXCompare(const std::shared_ptr<Geometry>& a, const std::shared_ptr<Geometry>& b);
bool BBYCompare(const std::shared_ptr<Geometry>& a, const std::shared_ptr<Geometry>& b);
bool BBZCompare(const std::shared_ptr<Geometry>& a, const std::shared_ptr<Geometry>& b);

void ObjectListSort(std::vector<std::shared_ptr<Geometry>>& object_list, int depth);

#endif //PATH_TRACER_GEOMETRY_H

