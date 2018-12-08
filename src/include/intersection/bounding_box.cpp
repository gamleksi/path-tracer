//
// Created by Aleksi Hämäläinen on 02/12/2018.
//

#include "bounding_box.h"

bool BoundingBox::RayHits(const ray<float>& ray, float t_min, float t_max) const {

  for(unsigned int d = 0; d < 3; d++) {

    auto invB = (float)1.0 / ray.Direction()[d];
    auto t0 = (min()[d] - ray.Origin()[d]) * invB;
    auto t1 = (max()[d] - ray.Origin()[d]) * invB;

    if (invB < (float)0.0) {
      std::swap(t0, t1);
    }

    t_min = (t0 > t_min) ? t0 : t_min;
    t_max = (t1 < t_max) ? t1 : t_max;

    if (t_max <= t_min) { return true; }

  }
  return true;
};


BoundingBox CombineBoxes(const BoundingBox& box1, const BoundingBox& box2) {

  vec3<float> t0(
      std::min(box1.min()[0], box2.min()[0]),
      std::min(box1.min()[1], box2.min()[1]),
      std::min(box1.min()[2], box2.min()[2])
      );
  vec3<float> t1(
    std::max(box1.max()[0], box2.min()[0]),
    std::max(box1.max()[1], box2.max()[1]),
    std::max(box1.max()[2], box2.max()[2])
    );

  return BoundingBox(t0, t1);
};
