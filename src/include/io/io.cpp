//
// Created by Jesse Miettinen on 28/11/2018.
//
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <sstream>
// for convenience
using json = nlohmann::json;
#include "geometry/geometry.h"


json ToJson(Geomlist *world){
    json j;
    json j2;
    Geometry ** objects = world->GetObjects();

    for (auto i = 0; i<world->GetObjectNum();i++){

        j["objnum"] = i+1;
        std::string str = "object";
        std::string s = std::to_string(i);
        str.insert(6,s);

        j["world"][str]["index"] = i+1;
        j["world"][str]["position"]["x"] = objects[i]->GetPosition()[0];
        j["world"][str]["position"]["y"] = objects[i]->GetPosition()[1];
        j["world"][str]["position"]["z"] = objects[i]->GetPosition()[2];
        j["world"][str]["radius"] = objects[i]->GetRadius();
    }

    j2 = j.dump();
    return j;
}
const std::string& SaveWorld(Geomlist *world){
    //opens the output file stream and uses ToJson to convert Geomlist * to Json format.

    std::cout<<"Give string for output filename"<<std::endl;
    std::string w_filename;
    std::cin>>w_filename;

    auto j2 = ToJson(world);

    std::ofstream os(w_filename);
    os << j2.dump();
    os.close();
    const std::string ref = w_filename;
    std::cout<<"sending this ref: "<<ref<<std::endl;
    return ref;
}


Geomlist* FromJson(json& j) {

    //std::cout << j << std::endl;
    //auto j2 = nlohmann::detail::parser<std::string>();
    //std::cout<<j2<<"!!!!!!"<<std::endl;
    //std::cout << "j.dump()" << j.dump() << std::endl;
    int x = j["objnum"];
    Geometry *li[x];

    std::string d = j.dump();
    auto j2 = j.parse(d);
    //std::cout << " We are here!!!" << j2 << std::endl;
    for (auto i = 0; i < x; i++) {
        float a, b, c, radius;


        std::string str = "object";
        std::string s = std::to_string(i);
        str.insert(6, s);

        a = j["world"][str]["position"]["x"];
        b = j["world"][str]["position"]["y"];
        c = j["world"][str]["position"]["z"];
        radius = j["world"][str]["radius"];
        li[i] = new Sphere(vec3<float>(a, b, c), radius);
    }
    Geomlist *world = new Geomlist(li, 3);
    Geometry ** objects = world->GetObjects();
    for (auto i = 0; i<world->GetObjectNum();i++){
        std::cout<<objects[i]->GetRadius();
    }
    return world;
}


Geomlist * LoadWorld(const std::string & filename) {
    //opens the input file stream and uses FromJson to convert Json to Geomlist * -format.
    std::cout<<std::endl<<"got this ref: "<<filename<<std::endl;
    std::ifstream file(filename);
    std::stringstream ss;
    if (file){

        ss << file.rdbuf();
        file.close();
    }
    std::string a = ss.str();
    auto j2 = json::parse(a);
    return FromJson(j2);
}