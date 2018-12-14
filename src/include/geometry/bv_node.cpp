//
// Created by Aleksi Hämäläinen on 14/12/2018.
//

#include "bv_node.h"

BoundingVolumeNode::BoundingVolumeNode(std::vector<std::shared_ptr<Geometry>>& object_list,
      float t0, float t1, int depth) {

  ObjectListSort(object_list, depth);
  depth = depth + 1;
  auto n_objects = object_list.size();

  if(n_objects == 1) {
    left_ = right_ = object_list[0];
  } else if(n_objects == 2) {
    left_ = object_list[0];
    right_ = object_list[1];
  } else {
    std::vector<std::shared_ptr<Geometry>> left_objects(object_list.begin(), object_list.begin() + n_objects / 2);
    std::vector<std::shared_ptr<Geometry>> right_objects(object_list.begin() + n_objects / 2, object_list.end());
    left_ = std::make_shared<BoundingVolumeNode>(left_objects, t0, t1, depth);
    right_ = std::make_shared<BoundingVolumeNode>(right_objects, t0, t1, depth);
  }

  BoundingBox left_box{}, right_box{};

  if (!(left_-> GetBoundingBox(t0, t1, left_box)) || !(right_-> GetBoundingBox(t0, t1, right_box))) {
    std::cerr << "Bounding box does not exist!" << std::endl;
  }
  bounding_box_ = CombineBoxes(left_box, right_box);
}

 int BoundingVolumeNode::NumberOfObjects() const {
   return NumberOfLeftObjects() + NumberOfRightObjects();
 }

 int BoundingVolumeNode::NumberOfLeftObjects() const {
   return left_->NumberOfObjects();
 }

 int BoundingVolumeNode::NumberOfRightObjects() const {
   return right_->NumberOfObjects();
 }

 bool BoundingVolumeNode::RayHits(const ray<float>& ray, float t_min, float t_max, HitRecord& rec) const {

  if (bounding_box_.RayHits(ray, t_min, t_max)) {
    HitRecord left_record{};
    HitRecord right_record{};

    bool left_hits = left_ -> RayHits(ray, t_min, t_max, left_record);
    bool right_hits = right_ -> RayHits(ray, t_min, t_max, right_record);

    if (left_hits && right_hits) {

      if(left_record.time < right_record.time) {
        rec = left_record;
      } else {
        rec = right_record;
      }

    } else if(left_hits) {
      rec = left_record;
    } else if(right_hits) {
      rec = right_record;
    }
    return left_hits || right_hits;
  } else { return false; }
}

bool BoundingVolumeNode::GetBoundingBox(float t0, float t1, BoundingBox& box) const {
  box = bounding_box_;
  return true;
}

