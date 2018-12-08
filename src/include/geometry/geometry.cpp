//
// Created by Jesse Miettinen on 14/11/2018.
//


#include "geometry/geometry.h"


Sphere::Sphere(vec3<float> position, float radius, std::shared_ptr<Material> mat)
    : Geometry(), radius_(radius), position_(position), material_(std::move(mat)) { }


bool Sphere::RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const
{
    vec3<float> oc = r.Origin() - position_;
    float a = Dot(r.Direction(), r.Direction());
    float b = Dot(oc, r.Direction());
    float c = Dot(oc,oc) - radius_*radius_;
    float discriminant = b*b - a*c;
    if (discriminant > 0){
        float temp = (-b - sqrtf(discriminant))/(a);
        if (temp < t_max && temp > t_min){
            rec.time = temp;
            rec.point = r.Point(rec.time);
            rec.normal = (rec.point - position_) / radius_;
            rec.mat_ptr = material_;
            return true;
        }
        temp = (-b + sqrtf(discriminant))/(a);
        if (temp < t_max && temp > t_min){
            rec.time = temp;
            rec.point = r.Point(rec.time);
            rec.normal = (rec.point - position_) / radius_;
            rec.mat_ptr = material_;
            return true;
        }
    }
    return false;
}


bool Sphere::GetBoundingBox(float t0, float t1, BoundingBox& box) const {
    box = BoundingBox(position_ - radius_, position_ + radius_);
    return true;
}

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
  return left_box.min()[1] - right_box.min()[1] >= 0.0;

};
bool BBZCompare(const std::shared_ptr<Geometry>& a, const std::shared_ptr<Geometry>& b) {
  BoundingBox left_box{}, right_box{};

  if(!a->GetBoundingBox(0.0, 0.0, left_box) || !b->GetBoundingBox(0.0, 0.0, right_box)) {
    std::cerr << "No bounding box exist" << std::endl;
  }
  return left_box.min()[2] - right_box.min()[2] >= 0.0;
};

void ObjectListSort(std::vector<std::shared_ptr<Geometry>>& object_list) {
  int axis = 1;  //(int)(2 * drand48());

  switch (axis) {
    case 1: std::sort(object_list.begin(), object_list.end(), BBXCompare);
    case 2: std::sort(object_list.begin(), object_list.end(), BBYCompare);
    default: std::sort(object_list.begin(), object_list.end(), BBZCompare);
  }
}

BoundingVolumeNode::BoundingVolumeNode(std::vector<std::shared_ptr<Geometry>>& object_list,
      float t0, float t1) {

  ObjectListSort(object_list);
  auto n_objects = object_list.size();

  if(n_objects == 1) {
    left_ = right_ = object_list[0];
  } else if(n_objects == 2) {
    left_ = object_list[0];
    right_ = object_list[1];
  } else {

    std::vector<std::shared_ptr<Geometry>> left_objects(object_list.begin(), object_list.begin() + n_objects / 2);
    std::vector<std::shared_ptr<Geometry>> right_objects(object_list.begin() + n_objects / 2, object_list.end());

    left_ = std::make_shared<BoundingVolumeNode>(left_objects, t0, t1);
    right_ = std::make_shared<BoundingVolumeNode>(right_objects, t0, t1);

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

 int Sphere::NumberOfObjects() const {
   return 1;
 }

 int Geomlist::NumberOfObjects() const {
   int i = 0;
   for (const auto &geom : list_) {
     i = i + geom -> NumberOfObjects();
   }
   return i;
 }

bool BoundingVolumeNode::RayHits(const ray<float>& ray, float t_min, float t_max, Hit_record& rec) const {

  if (bounding_box_.RayHits(ray, t_min, t_max)) {
    Hit_record left_record{};
    Hit_record right_record{};

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

