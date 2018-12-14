//
// Created by Jesse Miettinen on 14/11/2018.
//

#include "geometry/geometry.h"




bool BBXCompare(const std::shared_ptr<Geometry>& a, const std::shared_ptr<Geometry>& b) {

  BoundingBox left_box{}, right_box{};

  if(!a->GetBoundingBox(0.0, 0.0, left_box) || !b->GetBoundingBox(0.0, 0.0, right_box)) {
    std::cerr << "No bounding box exist" << std::endl;
  }
  return left_box.min()[0] - right_box.min()[0] > 0.0;
};

bool BBYCompare(const std::shared_ptr<Geometry>& a, const std::shared_ptr<Geometry>& b) {

  BoundingBox left_box{}, right_box{};

  if(!a->GetBoundingBox(0.0, 0.0, left_box) || !b->GetBoundingBox(0.0, 0.0, right_box)) {
    std::cerr << "No bounding box exist" << std::endl;
  }
  return left_box.min()[1] - right_box.min()[1] > 0.0;
};

bool BBZCompare(const std::shared_ptr<Geometry>& a, const std::shared_ptr<Geometry>& b) {
  BoundingBox left_box{}, right_box{};

  if(!a->GetBoundingBox(0.0, 0.0, left_box) || !b->GetBoundingBox(0.0, 0.0, right_box)) {
    std::cerr << "No bounding box exist" << std::endl;
  }
  return left_box.min()[2] - right_box.min()[2] > 0.0;
};

void ObjectListSort(std::vector<std::shared_ptr<Geometry>>& object_list, int depth) {
  int axis = depth % 3;

  if (axis == 0) {
    std::sort(object_list.begin(), object_list.end(), BBXCompare);
  } else if(axis == 1) {
    std::sort(object_list.begin(), object_list.end(), BBYCompare);
  } else {
    std::sort(object_list.begin(), object_list.end(), BBZCompare);
  }
}
