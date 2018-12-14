//
// Created by Jesse Miettinen on 21/11/2018.
//


#ifndef PATH_TRACER_IO_H
#define PATH_TRACER_IO_H
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include "geometry/geometry.h"
#include "camera/camera.h"
#include "material/material.h"
// for convenience
using json = nlohmann::json;



void SaveWorld(std::shared_ptr<Geomlist> &world, Camera& camera);
json ToJson(std::shared_ptr<Geomlist> &world, Camera& camera);

void LoadObjectList(const std::string & filename, std::vector<std::shared_ptr<Geometry>>& object_list);
void FromJson(const std::string& j, std::vector<std::shared_ptr<Geometry>>& object_list);
Camera LoadCamera(const std::string & filename);
std::shared_ptr<Sphere> LoadSphere(json& j,std::string& id);
std::shared_ptr<XyRect> LoadXyRect(json& j,std::string& id);
std::shared_ptr<XzRect> LoadXzRect(json& j,std::string& id);
std::shared_ptr<YzRect> LoadYzRect(json& j,std::string& id);
std::shared_ptr<YzRect> LoadBoxesYzRect(json& j,std::string& id, std::string &number);
std::shared_ptr<XzRect> LoadBoxesXzRect(json& j,std::string& id,std::string& number);
std::shared_ptr<XyRect> LoadBoxesXyRect(json& j,std::string& id,std::string& number);
std::shared_ptr<Box> LoadBox(json& j,std::string& id);

//namespace ns {
//    void to_json(json& j, const person& p) {
//        j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
//    }
//
//   void from_json(const json& j, person& p) {
//        j.at("name").get_to(p.name);
//        j.at("address").get_to(p.address);
//        j.at("age").get_to(p.age);
//    }
//};

#endif //PATH_TRACER_IO_H