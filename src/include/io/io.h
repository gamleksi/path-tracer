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



std::string SaveWorld(Geomlist& world, Camera& camera);
json ToJson(Geomlist& world, Camera& camera);

Geomlist LoadWorld(const std::string & filename);
Geomlist FromJson(const std::string& j);


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

#endif PATH_TRACER_IO_H