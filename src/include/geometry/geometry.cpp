//
// Created by Jesse Miettinen on 14/11/2018.
//

#include "geometry/geometry.h"
#include <pdf/onb.h>
#include <pdf/pdf.h>



XyRect::XyRect(float x0, float x1, float y0, float y1, float k, std::shared_ptr<Material> mat)
    : x0_(x0), x1_(x1), y0_(y0), y1_(y1), k_(k), material_(std::move(mat)) { }

XzRect::XzRect(float x0, float x1, float z0, float z1, float k, std::shared_ptr<Material> mat)
    : x0_(x0), x1_(x1), z0_(z0), z1_(z1), k_(k), material_(std::move(mat)) { }

YzRect::YzRect(float y0, float y1, float z0, float z1, float k, std::shared_ptr<Material> mat)
    : y0_(y0), y1_(y1), z0_(z0), z1_(z1), k_(k), material_(std::move(mat)) { }


bool XyRect::RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const {
    float t = (k_ - r.Origin().Z()) / r.Direction().Z();
    if (t < t_min || t > t_max){ return false; }
    float x = r.Origin().X() + t * r.Direction().X();
    float y = r.Origin().Y() + t * r.Direction().Y();
    if (x < x0_ || x > x1_ || y < y0_ || y > y1_) { return false; }
    rec.u = (x - x0_) / (x1_ - x0_);
    rec.v = (y - y0_) / (y1_ - y0_);
    rec.mat_ptr = material_;
    rec.point = r.Point(t);
    rec.normal = vec3<float>(0,0,1);
    return true;
}

bool XzRect::RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const {
    float t = (k_ - r.Origin().Y()) / r.Direction().Y();
    if (t < t_min || t > t_max) { return false; }
    float x = r.Origin().X() + t * r.Direction().X();
    float z = r.Origin().Z() + t * r.Direction().Z();
    if (x < x0_ || x > x1_ || z < z0_ || z > z1_) { return false; }
    rec.u = (x - x0_) / (x1_ - x0_);
    rec.v = (z - z0_) / (z1_ - z0_);
    rec.mat_ptr = material_;
    rec.point = r.Point(t);
    rec.normal = vec3<float>(0, 1, 0);
    return true;
}

bool YzRect::RayHits(const ray<float> &r, float t_min, float t_max, HitRecord &rec) const {
    float t = (k_ - r.Origin().X()) / r.Direction().X();
    if (t < t_min || t > t_max) { return false; }
    float y = r.Origin().Y() + t * r.Direction().Y();
    float z = r.Origin().Z() + t * r.Direction().Z();
    if (y < y0_ || y > y1_ || z < z0_ || z > z1_) { return false; }
    rec.u = (y - y0_) / (y1_ - y0_);
    rec.v = (z - z0_) / (z1_ - z0_);
    rec.mat_ptr = material_;
    rec.point = r.Point(t);
    rec.normal = vec3<float>(1, 0, 0);
    return true;
}

bool XyRect::GetBoundingBox(float t0, float t1, BoundingBox &box) const {
    box = BoundingBox(vec3<float>(x0_,y0_,k_-0001), vec3<float>(x1_,y1_,k_+0001));
    return true;
}

bool XzRect::GetBoundingBox(float t0, float t1, BoundingBox &box) const {
    box = BoundingBox(vec3<float>(x0_,k_-0.0001,z0_), vec3<float>(x1_,k_+0.0001,z1_));
    return true;
}

bool YzRect::GetBoundingBox(float t0, float t1, BoundingBox &box) const {
    box = BoundingBox(vec3<float>(k_-0.0001,y0_,z0_), vec3<float>(k_+0.0001,y1_,z1_));
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

 int XyRect::NumberOfObjects() const {
    return 1;
 }

 int XzRect::NumberOfObjects() const {
    return 1;
 }

 int YzRect::NumberOfObjects() const {
    return 1;
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




bool Sphere::RayHits(const ray<float>& r, float t_min, float t_max, HitRecord& rec) const
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


float Sphere::PdfValue(const vec3<float>& o, const vec3<float>& v) const {
    HitRecord rec;
    if (this->RayHits(ray<float>(o, v), 0.001, MAXFLOAT, rec)) {
        float cos_theta_max = sqrt(1 - radius_*radius_/(position_-o).Squared_length());
        float solid_angle = 2*M_PI*(1-cos_theta_max);
        return  1 / solid_angle;
    }
    else
        return 0;
}


vec3<float> Sphere::Random(const vec3<float> &o) const {
    vec3<float> direction = position_ - o;
    float distance_squared = direction.Squared_length();
    Onb uvw;
    uvw.Build_from_w(direction);
    return uvw.Local(RandomToSphere(radius_, distance_squared));
}


int Sphere::NumberOfObjects() const {
    return 1;
}


bool Geomlist::RayHits(const ray<float>& r, float t_min, float t_max, HitRecord& rec) const{
    HitRecord temp_rec{};
    bool hit = false;
    float closest_distance = t_max;
    for (int i = 0; i < list_size; i++){
        if(list[i]->RayHits(r, t_min, closest_distance, temp_rec)){
            hit = true;
            closest_distance = temp_rec.time;
            rec = temp_rec;
        }
    }
    return hit;
}

bool Geomlist::GetBoundingBox(float t0, float t1, BoundingBox& box) const {
    if ( list_size < 1) { return false; }

    BoundingBox temporary_box;
    bool first_bounding_exist = list[0]->GetBoundingBox(t0, t1, temporary_box);

    if (first_bounding_exist) {
        box = temporary_box;
    } else {
        return false;
    }

    for (unsigned int i = 1; i < list_size; i++) {

        if(list[i]->GetBoundingBox(t0, t1, temporary_box)) {
            box = CombineBoxes(box, temporary_box);
        } else {
            return false;
        }
    }
    return true;
}





float Geomlist::PdfValue(const vec3<float> &o, const vec3<float> &v) const {
    float weight = 1.0/list_size;
    float sum = 0;
    for (int i = 0; i < list_size; i++)
        sum += weight*list[i]->PdfValue(o, v);
    return sum;
}

vec3<float> Geomlist::Random(const vec3<float>& o) const {
    int index = int(drand48() * list_size);
    return list[ index ]->Random(o);
}

int Geomlist::NumberOfObjects() const {
    int i = 0;
    for (const auto &geom : list) {
        i = i + geom -> NumberOfObjects();
    }
    return i;
}






float  XyRect::PdfValue(const vec3<float>& o, const vec3<float>& v) const {
    HitRecord rec;
    if (this->RayHits(ray<float>(o, v), 0.001, MAXFLOAT, rec)) {
        float area = (x1_-x0_)*(y1_-y0_);
        float distance_squared = rec.time * rec.time * v.Squared_length();
        float cosine = fabs(Dot(v, rec.normal) / v.Squared_length());
        return  distance_squared / (cosine * area);
    }
    else
        return 0;
}
vec3<float> XyRect::Random(const vec3<float>& o) const {
    vec3<float> random_point = vec3<float>(x0_ + drand48()*(x1_-x0_), k_, y0_ + drand48()*(y1_-y0_));
    return random_point - o;
}

float  XzRect::PdfValue(const vec3<float>& o, const vec3<float>& v) const {
    HitRecord rec;
    if (this->RayHits(ray<float>(o, v), 0.001, MAXFLOAT, rec)) {
        float area = (x1_-x0_)*(z1_-z0_);
        float distance_squared = rec.time * rec.time * v.Squared_length();
        float cosine = fabs(Dot(v, rec.normal) / v.Squared_length());
        return  distance_squared / (cosine * area);
    }
    else
        return 0;
}
vec3<float> XzRect::Random(const vec3<float>& o) const {
    vec3<float> random_point = vec3<float>(x0_ + drand48()*(x1_-x0_), k_, z0_ + drand48()*(z1_-z0_));
    return random_point - o;
}


float  YzRect::PdfValue(const vec3<float>& o, const vec3<float>& v) const {
    HitRecord rec;
    if (this->RayHits(ray<float>(o, v), 0.001, MAXFLOAT, rec)) {
        float area = (y1_-y0_)*(y1_-y0_);
        float distance_squared = rec.time * rec.time * v.Squared_length();
        float cosine = fabs(Dot(v, rec.normal) / v.Squared_length());
        return  distance_squared / (cosine * area);
    }
    else
        return 0;
}
vec3<float> YzRect::Random(const vec3<float>& o) const {
    vec3<float> random_point = vec3<float>(y0_ + drand48()*(y1_-y0_), k_, y0_ + drand48()*(y1_-y0_));
    return random_point - o;
}

