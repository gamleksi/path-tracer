//
// Created by Jesse on 12.11.2018.
//
#include "vec3.h"


enum Material
{
  Matte,
  Glass
  Metal
};

class Geometry {
  public:
    //constructor - add material when ready
    Geometry(std::string& name = "abc", Material mat = Matte, vec3 position = vec3(1,2,3))
      : name_(name), material_(mat), position_(position) { }
    //destructor virtual
    virtual ~Geometry() { };
    //clone virtual, maybe not needed
    virtual Geometry* clone() const{
      return new Geometry(*this.get_Name(), *this.get_Material(), *this.get_Position());
    }
    //some utilities, maybe needed get etc
    std::string get_Name(){
      return name_; //needs to be a const ref most likely
    }
    Material get_Material(){
      return material_;
    }
    ve3 get_Position(){
      return position_;
    }


  private:
    //name, material and position vec3
    std::string name_;
    Material material_; // not implemented yet.
    vec3 position_;
};

class Sphere : public Geometry{
  //RayHits algorithm by Peter Shirley, from Ray Tracing in One Weekend, version 1.55
  public:
    Sphere(std::string& name = "abc", Material mat = Matte, vec3 position = vec3(1,2,3), float radius)
    : Geometry(name, mat, position), radius_(radius) { }
    //get radius and ray hits Sphere
    virtual ~Sphere() { };
    float get_Radius(){
      return radius_;
    }
    bool RayHits(const ray& r)
    //discriminant stuff
    {
      vec3 pos = get_Position();
      vec3 oc = r.origin() - position_;
      float a = dot(r.direction(), r.direction());
      float b = 2.0 * dot(oc, r.direction());
      float c = dot(oc,oc) - radius_*radius_;
      float discriminant = b*b - 4*a*c;
      return (discriminant > 0);
    }


  private:
    //radius here
    float radius_;

};
