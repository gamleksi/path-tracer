//
// Created by Aleksi Hämäläinen on 14/12/2018.
//

#ifndef PATH_TRACER_BV_NODE_H
#define PATH_TRACER_BV_NODE_H

#include "geometry/geometry.h"

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

#endif //PATH_TRACER_BV_NODE_H
