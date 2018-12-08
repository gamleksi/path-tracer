//
// Created by Aleksi Hämäläinen on 02/12/2018.
//

#ifndef PATH_TRACER_BOUNDING_BOX_H
#define PATH_TRACER_BOUNDING_BOX_H

#include <vector/vec3.h>
#include <ray/ray.h>

class BoundingBox {

 public:
  BoundingBox() = default;
  BoundingBox(const vec3<float>& min, const vec3<float>& max) : min_(min), max_(max) {};

  vec3<float> min() const { return min_; }
  vec3<float> max() const { return max_; }

  bool RayHits(const ray<float>& r, float t_min, float t_max) const;

 private:

  vec3<float> min_;
  vec3<float> max_;

};

BoundingBox CombineBoxes(const BoundingBox& box1, const BoundingBox& box2);

#endif //PATH_TRACER_BOUNDING_BOX_H
