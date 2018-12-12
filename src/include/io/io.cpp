//
// Created by Jesse Miettinen on 28/11/2018.
//
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include "io.h"



// for convenience
using json = nlohmann::json;

// Own functions for saving and loading for camera, geomlist and Sphere

json ToJson(std::shared_ptr<Geomlist> &world, Camera& camera){

    json j;
    std::cout<<world->GetListSize()<<std::endl;
    std::cout<<world->NumberOfObjects()<<std::endl;
    std::vector<std::shared_ptr<Geometry>> list = world->GetObjects();
    int x = world->GetListSize();
    j["objnum"] = x;
    camera.ToJson(j);
//    for (auto i = 0; i<x;i++){

//        std::string str = "object";
//        std::string s = std::to_string(i);
//        str.insert(6,s);
//        list[i]->ToJson(j,i+1,str);
//        auto mat = list[i]->GetMaterial();
//        mat->ToJson(j, str);
//    }

    return j;
}
void SaveWorld(std::shared_ptr<Geomlist> &world, Camera& camera){
    //opens the output file stream and uses ToJson to convert to Json format, then dumps Json file to outputstream.

    std::cout<<"Give string for output filename"<<std::endl;
    std::string w_filename;
    std::cin>>w_filename;

    auto j = ToJson(world,camera);

    std::ofstream os(w_filename);
    os << j.dump();
    os.close();
    std::string ref = w_filename;
    std::cout<<"sending this ref: "<<ref<<std::endl;
}


//Geomlist FromJson(const std::string& str) {

    //std::cout << j << std::endl;
    //auto j2 = nlohmann::detail::parser<std::string>();
    //std::cout<<j2<<"!!!!!!"<<std::endl;
    //std::cout << "j.dump()" << j.dump() << std::endl;
//    json j = json::parse(str);
//    int x = j["objnum"];

//    std::vector<std::shared_ptr<Geometry>> object_list;

    //std::cout << " We are here!!!" << j << std::endl;

//    for (auto i = 0; i < x; i++) {
//        float X, Y, Z, radius, a,b,c;


//        std::string str = "object";
//        std::string s = std::to_string(i);
//        str.insert(6, s);

//        X = j["world"][str]["position"]["x"];
//        Y = j["world"][str]["position"]["y"];
//        Z = j["world"][str]["position"]["z"];
//        radius = j["world"][str]["radius"];
//        a = j["world"][str]["mat"]["albedo"]["0"];
//        b = j["world"][str]["mat"]["albedo"]["1"];
//        c = j["world"][str]["mat"]["albedo"]["2"];
//        std::shared_ptr<Sphere> sphere =
//                std::make_shared<Sphere>(vec3<float>(X, Y, Z), radius, std::make_shared<Metal>(vec3<float>(a,b,c)));

//        object_list.push_back(sphere);
//    }
//    Geomlist world(x, object_list);
//    return world;
//}


//Geomlist LoadWorld(const std::string & filename) {
    //opens the input file stream and uses FromJson to convert Json to Geomlist * -format.
//    std::cout<<std::endl<<"got this ref: "<<filename<<std::endl;
//    std::ifstream file(filename);
//    std::stringstream ss;
//    if (file){
//        ss << file.rdbuf();
//        file.close();
//    }
//    std::string a = ss.str();
//    return FromJson(a);
//}