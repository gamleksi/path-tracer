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
    std::string str = "Initiating Saving algorithm";
    world->ToJson(j,str);

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

std::shared_ptr<Sphere> LoadSphere(json& j, std::string& id){
    vec3<float> white(0.9,0.9,0.9);
    std::shared_ptr<Material> white_material;
    white_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(white));
    std::shared_ptr<Sphere> sphere;

    float X, Y, Z, radius;
//  float a,b,c;
    X = j["world"][id]["position"]["x"];
    Y = j["world"][id]["position"]["y"];
    Z = j["world"][id]["position"]["z"];
    radius = j["world"][id]["radius"];
//        a = j["world"][id]["mat"]["albedo"]["0"];
//        b = j["world"][id]["mat"]["albedo"]["1"];
//        c = j["world"][id]["mat"]["albedo"]["2"];

    sphere = std::make_shared<Sphere>(vec3<float>(X,Y,Z), radius, white_material);
    return sphere;
}

void FromJson(const std::string& str,std::vector<std::shared_ptr<Geometry>>& object_list) {

    //std::cout << j << std::endl;
    //auto j2 = nlohmann::detail::parser<std::string>();
    //std::cout<<j2<<"!!!!!!"<<std::endl;
    //std::cout << "j.dump()" << j.dump() << std::endl;
    std::string type_sphere = "Sphere";
    std::string type_XyRect = "XyRect";
    std::string type_XzRect = "XzRect";
    std::string type_YzRect = "YzRect";
    std::string type_FlipNormal = "FlipNormal";
    json j = json::parse(str);
    int x = j["objnum"];

    //std::cout << " We are here!!!" << j << std::endl;

    for (auto i = 0; i < x; i++) {



        std::string str = "object";
        std::string s = std::to_string(i);
        str.insert(6, s);
        if(j["world"][str]["type"]==type_sphere){
            auto object = LoadSphere(j, str);
            object_list.push_back(object);
        }
    }

//        std::shared_ptr<Sphere> sphere =
//                std::make_shared<Sphere>(vec3<float>(X, Y, Z), radius, std::make_shared<Metal>(vec3<float>(a,b,c)));

//        object_list.push_back(sphere);
//    }
//    Geomlist world(x, object_list);
 //   return world;
}


void LoadObjectList(const std::string & filename,std::vector<std::shared_ptr<Geometry>>& object_list) {
    //opens the input file stream and uses FromJson to convert Json to Geomlist * -format.
    std::cout<<std::endl<<"got this ref: "<<filename<<std::endl;
    std::ifstream file(filename);
    std::stringstream ss;
    if (file){
        ss << file.rdbuf();
        file.close();
    }
    std::string a = ss.str();
    FromJson(a, object_list);
}

Camera LoadCamera(const std::string & filename){
    std::ifstream file(filename);
    std::stringstream ss;
    if(file){
        ss << file.rdbuf();
        file.close();
    }
    std::string a = ss.str();
    json j = json::parse(a);
    vec3<float> u(j["camera"]["U"]["x"],j["camera"]["U"]["y"],j["camera"]["U"]["z"]);
    vec3<float> v(j["camera"]["V"]["x"],j["camera"]["V"]["y"],j["camera"]["V"]["z"]);
    vec3<float> origin_(j["camera"]["Origin"]["x"],j["camera"]["Origin"]["y"],j["camera"]["Origin"]["z"]);
    vec3<float> llc(j["camera"]["LLC"]["x"],j["camera"]["LLC"]["y"],j["camera"]["LLC"]["z"]);
    vec3<float> hor(j["camera"]["Horizontal"]["x"],j["camera"]["Horizontal"]["y"],j["camera"]["Horizontal"]["z"]);
    vec3<float> ver(j["camera"]["Vertical"]["x"],j["camera"]["Vertical"]["y"],j["camera"]["Vertical"]["z"]);
    float lens_radius=j["camera"]["LensRadius"];
    Camera camera(u,v,origin_,llc,hor,ver,lens_radius);
    return camera;

}