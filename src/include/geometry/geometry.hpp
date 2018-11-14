//
// Created by Jesse on 12.11.2018.
//
#include "vector/vec3.h"
#include "ray.h"


enum Material
{
  Matte,
  Glass,
  Metal
};

class Geometry {
  public:
    //constructor - change material when ready
    Geometry(std::string name = "abc", Material mat = Matte, vec3<float> position = vec3<float>(1.0,2.0,3.0))
      : name_(name), material_(mat), position_(position) { }
    //destructor virtual
    virtual ~Geometry() { };
    //clone virtual, maybe not needed
    virtual Geometry* clone() const{
      return new Geometry(this->get_Name(), this->get_Material(), this->get_Position());
    }
    //some utilities, maybe needed get etc
    std::string get_Name() const{
      return name_; //needs to be a const ref most likely
    }
    Material get_Material() const{
      return material_;
    }
    vec3<float> get_Position() const{
      return position_;
    }


  private:
    //name, material and position vec3
    std::string name_;
    Material material_; // not implemented yet.
    vec3<float> position_;
};

class Sphere : public Geometry{
  //RayHits algorithm by Peter Shirley, from Ray Tracing in One Weekend, version 1.55
  public:
    Sphere(std::string name = "abc", Material mat = Matte, vec3<float> position = vec3<float>(1.0,2.0,3.0), float radius = 0.0)
    : Geometry(name, mat, position), radius_(radius) { }
    //get radius and ray hits Sphere
    virtual ~Sphere() { };
    float get_Radius(){
      return radius_;
    }
    bool RayHits(const ray<float>& r)
    //discriminant stuff
    {
      vec3<float> pos = get_Position();
      vec3<float> oc = r.origin() - pos;
      float a = cross(r.direction(), r.direction()); // function should be called dot, instead of cross
      float b = 2.0 * cross(oc, r.direction());
      float c = cross(oc,oc) - radius_*radius_;
      float discriminant = b*b - 4*a*c;
      return (discriminant > 0);
    }


  private:
    //radius here
    float radius_;

};
