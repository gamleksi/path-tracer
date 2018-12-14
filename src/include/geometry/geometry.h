#include <utility>
#include <algorithm>
#include <iostream>

//
// Created by Jesse Miettinen on 14/11/2018.
//

#ifndef PATH_TRACER_GEOMETRY_H
#define PATH_TRACER_GEOMETRY_H

#include <vector>
#include "vector/vec3.h"
#include "ray/ray.h"
#include "intersection/bounding_box.h"
#include <nlohmann/json.hpp>
// for convenience
using json = nlohmann::json;

class Material;

struct Hit_record{ // TODO Fix the name
  float time;
  float u;
  float v;
  vec3<float> point;
  vec3<float> normal;
  std::shared_ptr<Material> mat_ptr;
};


class Geometry {
 public:
 virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const = 0;
 virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const = 0;
 virtual int NumberOfObjects() const=0;
 virtual void ToJson(json& j,std::string& id)const = 0;
 virtual std::vector<std::shared_ptr<Material>> GetMaterials()const = 0;
};

class Sphere : public Geometry{
  //RayHits algorithm by Peter Shirley, from Ray Tracing in One Weekend, version 1.55
 public:

  Sphere(vec3<float> position, float radius, std::shared_ptr<Material> mat);

  ~Sphere() =default;

  virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
  virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
  virtual int NumberOfObjects() const;
  virtual void ToJson(json& j,std::string& id)const;
  virtual std::vector<std::shared_ptr<Material>> GetMaterials()const;

  std::string GetType()const {return type_;}
  vec3<float> GetPosition()const{return position_;}
  //std::shared_ptr<Material> GetMaterial()const{return material_;}
  float GetRadius()const {return radius_;}

 private:
  //radius here
  float radius_;
  std::shared_ptr<Material> material_;
  vec3<float> position_;
  std::string type_ = "Sphere";
};

class XyRect : public Geometry{
public:
    XyRect(float x0, float x1, float y0, float y1, float k, std::shared_ptr<Material> mat);

    ~XyRect() =default;
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
    virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
    virtual int NumberOfObjects() const;
    virtual void ToJson(json& j,std::string& id)const;

    virtual std::vector<std::shared_ptr<Material>> GetMaterials()const;
    std::string GetType()const {return type_;}
    float GetX0()const{return x0_;}
    float GetX1()const{return x1_;}
    float GetY0()const{return y0_;}
    float GetY1()const{return y1_;}
    float GetK()const{return k_;}
    //std::shared_ptr<Material> GetMaterial() const{return material_;}
private:
    float x0_, x1_, y0_, y1_, k_;
    std::shared_ptr<Material> material_;
    std::string type_ = "XyRect";
};

class XzRect : public Geometry{
public:
    XzRect(float x0, float x1, float z0, float z1, float k, std::shared_ptr<Material> mat);

    ~XzRect() = default;
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
    virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
    virtual int NumberOfObjects() const;
    virtual void ToJson(json& j,std::string& id)const;

    virtual std::vector<std::shared_ptr<Material>> GetMaterials()const;
    std::string GetType()const {return type_;}
    float GetX0()const{return x0_;}
    float GetX1()const{return x1_;}
    float GetZ0()const{return z0_;}
    float GetZ1()const{return z1_;}
    float GetK()const{return k_;}
    //std::shared_ptr<Material> GetMaterial() const{return material_;}
private:
    float x0_, x1_, z0_, z1_, k_;
    std::shared_ptr<Material> material_;
    std::string type_ = "XzRect";
};

class YzRect : public Geometry{
public:
    YzRect(float y0, float y1, float z0, float z1, float k, std::shared_ptr<Material> mat);

    ~YzRect() = default;
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
    virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
    virtual int NumberOfObjects() const;
    virtual void ToJson(json& j,std::string& id)const;

    virtual std::vector<std::shared_ptr<Material>> GetMaterials()const;
    std::string GetType()const {return type_;}
    float GetY0()const{return y0_;}
    float GetY1()const{return y1_;}
    float GetZ0()const{return z0_;}
    float GetZ1()const{return z1_;}
    float GetK()const{return k_;}
    //std::shared_ptr<Material> GetMaterial() const{return material_;}
private:
    float y0_, y1_, z0_, z1_, k_;
    std::shared_ptr<Material> material_;
    std::string type_ = "YzRect";
};

class FlipNormals : public Geometry{
public:
    FlipNormals(std::shared_ptr<Geometry> p) : ptr_(p) { }
    ~FlipNormals() = default;
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const {
        if (ptr_->RayHits(r, t_min, t_max, rec)) {
            rec.normal = -rec.normal;
            return true;
        } else {
            return false;
        }
    }
    virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const{
        return ptr_->GetBoundingBox(t0, t1, box);
    }
    virtual int NumberOfObjects() const { return 1; }
    virtual void ToJson(json& j,std::string& id)const;

    virtual std::vector<std::shared_ptr<Material>> GetMaterials()const;
    std::string GetType()const {return type_;}
    std::shared_ptr<Geometry> GetPtr() const{return ptr_;}
private:
    std::shared_ptr<Geometry> ptr_;
    std::string type_ = "FlipNormals";
};

class Geomlist : public Geometry{
 public:

    Geomlist(){}

    Geomlist(std::vector<std::shared_ptr<Geometry>>& object_list)
    : list_size_((int)object_list.size()), list_(object_list) {}

    int GetListSize()const{return list_size_;}
    std::vector<std::shared_ptr<Geometry>> GetObjects() const{return list_;}
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
    virtual std::vector<std::shared_ptr<Material>> GetMaterials()const;
    virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
    virtual int NumberOfObjects() const;
    virtual void ToJson(json& j,std::string& id)const;
    void BoxToJson(json&j, std::string& id)const;
    std::string GetType()const {return type_;}

 private:
    std::vector<std::shared_ptr<Geometry>> list_;
    int list_size_;
    std::string type_ = "GeomList";

};

class Box : public Geometry {
public:
    Box() { }
    Box(const vec3<float>& p0, const vec3<float>& p1, std::shared_ptr<Material> mat);
    Box(vec3<float>& p0, vec3<float> &p1, std::shared_ptr<Geomlist> g) : pmin_(p0), pmax_(p1), list_ptr_(g) {}
    ~Box() = default;
    virtual bool RayHits(const ray<float>& r, float t_min, float t_max, Hit_record& rec) const;
    virtual bool GetBoundingBox(float t0, float t1, BoundingBox& box) const;
    virtual int NumberOfObjects() const;
    virtual void ToJson(json& j,std::string& id)const;

    virtual std::vector<std::shared_ptr<Material>> GetMaterials()const;
    std::string GetType()const {return type_;}
    vec3<float> GetPMin()const {return pmin_;}
    vec3<float> GetPMax()const{return pmax_;}
    std::shared_ptr<Geomlist> GetWalls()const {return list_ptr_;}

private:
    vec3<float> pmin_, pmax_;
    std::shared_ptr<Geomlist> list_ptr_;
    std::string type_ = "Box";
};

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
  virtual void ToJson(json& j,std::string& id)const;
  virtual std::vector<std::shared_ptr<Material>> GetMaterials()const;
  std::string GetType()const {return type_;}

 private:
  std::shared_ptr<Geometry> left_;
  std::shared_ptr<Geometry> right_;
  BoundingBox bounding_box_;
  std::string type_ = "BoundingVolumeNode";

};

bool BBXCompare(const std::shared_ptr<Geometry>& a, const std::shared_ptr<Geometry>& b);
bool BBYCompare(const std::shared_ptr<Geometry>& a, const std::shared_ptr<Geometry>& b);
bool BBZCompare(const std::shared_ptr<Geometry>& a, const std::shared_ptr<Geometry>& b);

void ObjectListSort(std::vector<std::shared_ptr<Geometry>>& object_list, int depth);
bool BoxOwnsThis(std::string& id);
#endif //PATH_TRACER_GEOMETRY_H

