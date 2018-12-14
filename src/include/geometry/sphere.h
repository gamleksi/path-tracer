//
// Created by Aleksi Hämäläinen on 14/12/2018.
//

#ifndef PATH_TRACER_SPHERE_H
#define PATH_TRACER_SPHERE_H

#include "geometry/geometry.h"

class Sphere : public Geometry{
  //RayHits algorithm by Peter Shirley, from Ray Tracing in One Weekend, version 1.55
 public:

  Sphere(vec3<float> position, float radius, std::shared_ptr<Material> mat);

  ~Sphere() { };
  float GetRadius() const {
      return radius_;
  }

  vec3<float> GetPosition() const { return position_; };

  virtual bool RayHits(const ray<float>& r, float t_min, float t_max, HitRecord& rec) const;
  virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
  virtual int NumberOfObjects() const;

 private:
  //radius here
  float radius_;
  std::shared_ptr<Material> material_;
  vec3<float> position_;
};

#endif //PATH_TRACER_SPHERE_H
