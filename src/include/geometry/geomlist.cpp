//
// Created by Aleksi Hämäläinen on 14/12/2018.
//

#include "geomlist.h"

bool Geomlist::RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const{
    Hit_record temp_rec{};
    bool hit = false;
    float closest_distance = t_max;
    for (int i = 0; i < list_size_; i++){
        if(list_[i]->RayHits(r, t_min, closest_distance, temp_rec)){
            hit = true;
            closest_distance = temp_rec.time;
            rec = temp_rec;
        }
    }
    return hit;
}

bool Geomlist::GetBoundingBox(float t0, float t1, BoundingBox& box) const {
  if ( list_size_ < 1) { return false; }

  BoundingBox temporary_box;
  bool first_bounding_exist = list_[0]->GetBoundingBox(t0, t1, temporary_box);

  if (first_bounding_exist) {
      box = temporary_box;
  } else {
      return false;
  }

  for (unsigned int i = 1; i < list_size_; i++) {

      if(list_[i]->GetBoundingBox(t0, t1, temporary_box)) {
          box = CombineBoxes(box, temporary_box);
      } else {
          return false;
      }
  }
  return true;
}

int Geomlist::NumberOfObjects() const {
  int i = 0;
  for (const auto &geom : list_) {
    i = i + geom -> NumberOfObjects();
  }
  return i;
}

