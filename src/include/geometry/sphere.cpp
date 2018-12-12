//
// Created by Jan Lundström on 2018-12-12.
//

#include <pdf/onb.h>
#include <pdf/pdf.h>
#include "sphere.h"

//bool Sphere::RayHits(const ray<float>& r, float t_min, float t_max, HitRecord& rec) const
//{
//    vec3<float> oc = r.Origin() - position_;
//    float a = Dot(r.Direction(), r.Direction());
//    float b = Dot(oc, r.Direction());
//    float c = Dot(oc,oc) - radius_*radius_;
//    float discriminant = b*b - a*c;
//    if (discriminant > 0){
//        float temp = (-b - sqrtf(discriminant))/(a);
//        if (temp < t_max && temp > t_min){
//            rec.time = temp;
//            rec.point = r.Point(rec.time);
//            rec.normal = (rec.point - position_) / radius_;
//            rec.mat_ptr = material_;
//            return true;
//        }
//        temp = (-b + sqrtf(discriminant))/(a);
//        if (temp < t_max && temp > t_min){
//            rec.time = temp;
//            rec.point = r.Point(rec.time);
//            rec.normal = (rec.point - position_) / radius_;
//            rec.mat_ptr = material_;
//            return true;
//        }
//    }
//    return false;
//}
//
//bool Sphere::GetBoundingBox(float t0, float t1, BoundingBox& box) const {
//    box = BoundingBox(position_ - radius_, position_ + radius_);
//    return true;
//}
//
//
//float Sphere::PdfValue(const vec3<float>& o, const vec3<float>& v) const {
//    HitRecord rec;
//    if (this->RayHits(ray<float>(o, v), 0.001, MAXFLOAT, rec)) {
//        float cos_theta_max = sqrt(1 - radius_*radius_/(position_-o).Squared_length());
//        float solid_angle = 2*M_PI*(1-cos_theta_max);
//        return  1 / solid_angle;
//    }
//    else
//        return 0;
//}
//
//
//vec3<float> Sphere::Random(const vec3<float> &o) const {
//    vec3<float> direction = position_ - o;
//    float distance_squared = direction.Squared_length();
//    Onb uvw;
//    uvw.Build_from_w(direction);
//    return uvw.Local(RandomToSphere(radius_, distance_squared));
//}
//
//
//int Sphere::NumberOfObjects() const {
//    return 1;
//}