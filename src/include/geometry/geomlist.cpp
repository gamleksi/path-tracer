//
// Created by Jan Lundström on 2018-12-12.
//

#include "geomlist.h"


//bool Geomlist::RayHits(const ray<float>& r, float t_min, float t_max, HitRecord& rec) const{
//    HitRecord temp_rec{};
//    bool hit = false;
//    float closest_distance = t_max;
//    for (int i = 0; i < list_size; i++){
//        if(list[i]->RayHits(r, t_min, closest_distance, temp_rec)){
//            hit = true;
//            closest_distance = temp_rec.time;
//            rec = temp_rec;
//        }
//    }
//    return hit;
//}
//
//bool Geomlist::GetBoundingBox(float t0, float t1, BoundingBox& box) const {
//    if ( list_size < 1) { return false; }
//
//    BoundingBox temporary_box;
//    bool first_bounding_exist = list[0]->GetBoundingBox(t0, t1, temporary_box);
//
//    if (first_bounding_exist) {
//        box = temporary_box;
//    } else {
//        return false;
//    }
//
//    for (unsigned int i = 1; i < list_size; i++) {
//
//        if(list[i]->GetBoundingBox(t0, t1, temporary_box)) {
//            box = CombineBoxes(box, temporary_box);
//        } else {
//            return false;
//        }
//    }
//    return true;
//}
//
//
//
//
//
//float Geomlist::PdfValue(const vec3<float> &o, const vec3<float> &v) const {
//    float weight = 1.0/list_size;
//    float sum = 0;
//    for (int i = 0; i < list_size; i++)
//        sum += weight*list[i]->PdfValue(o, v);
//    return sum;
//}
//
//vec3<float> Geomlist::Random(const vec3<float>& o) const {
//    int index = int(drand48() * list_size);
//    return list[ index ]->Random(o);
//}
//
//int Geomlist::NumberOfObjects() const {
//    int i = 0;
//    for (const auto &geom : list) {
//        i = i + geom -> NumberOfObjects();
//    }
//    return i;
//}

