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
    //j["pi"] = 3.141;
    Geometry ** objects = world->GetObjects();
    std::cout<<" received *world with object amount: "<< world->GetObjectNum()<<std::endl;
    for (auto i = 0; i<world->GetObjectNum();i++){
        std::cout<<"Objectamount: "<<world->GetObjectNum()<<" i: "<< i<<std::endl;
        //std::cout<<world->GetPosition()<<std::endl;
        j["objnum"] = i+1;
        std::string str = "object";
        std::string s = std::to_string(i);
        std::cout << s<<std::endl;
        str.insert(6,s);
        j["world"][str]["index"] = i+1;
        j["world"][str]["position"]["x"] = objects[i]->GetPosition()[0];
        j["world"][str]["position"]["y"] = objects[i]->GetPosition()[1];
        j["world"][str]["position"]["z"] = objects[i]->GetPosition()[2];
        j["world"][str]["radius"] = objects[i]->GetRadius();
    }

    j2 = j.dump();
    //std::cout << j2 << " ! "<<std::endl;
    //for (auto& element : j) {
//        std::cout<<"!!" << element << '\n';
//    }
    return j;
}
const std::string& SaveWorld(Geomlist *world){
    //opens the output file stream and uses ToJson to convert Geomlist * to Json format.
    std::cout<<"Give string for filename"<<std::endl;
    std::string w_filename;
    std::cin>>w_filename;
    const std::string & ref = w_filename;
    std::ofstream os(w_filename);

    auto j2 = ToJson(world);
    os << j2.dump();
    os.close();

    return ref;
}


Geomlist * FromJson(json& j) {

    std::cout << j << std::endl;
    //auto j2 = nlohmann::detail::parser<std::string>();
    //std::cout<<j2<<"!!!!!!"<<std::endl;
    std::cout << "j.dump()" << j.dump() << std::endl;
    int x = j["objnum"];
    Geometry *li[x];

    std::string d = j.dump();
    auto j2 = j.parse(d);
    std::cout << " We are here!!!" << j2 << std::endl;
    for (auto i = 0; i < x; i++) {
        std::cout << i << std::endl;
        float a, b, c, radius;


        std::string str = "object";
        std::string s = std::to_string(i);
        str.insert(6, s);
        std::cout << str << "!" << std::endl;
        std::cout << j["world"][str].dump();

        a = j["world"][str]["position"]["x"];
        //std::cout<<std::endl<<j["world"][str]["position"]["x"]<<" ! "<<a<<" ! this was a"<<std::endl;
        //std::cout<<std::endl<<j["world"][str].dump()<<" ! "<<" ! this was a"<<std::endl;
        std::cout << std::endl << "x: " << a;
        b = j["world"][str]["position"]["y"];
        std::cout << std::endl << "y: " << b;
        c = j["world"][str]["position"]["z"];
        std::cout << std::endl << "z: " << c;
        radius = j["world"][str]["radius"];
        std::cout << std::endl << "radius: " << radius;
        li[i] = new Sphere(vec3<float>(a, b, c), radius);
    }
    Geomlist *world = new Geomlist(li, 3);
    Geometry **objects = world->GetObjects();
    for (auto i = 0; i < world->GetObjectNum(); i++) {
        std::cout << std::endl << "i: " << i << " x: " << objects[i]->GetPosition()[0] << " ";
        std::cout << "i: " << i << " y: " << objects[i]->GetPosition()[1] << " ";
        std::cout << "i: " << i << " z: " << objects[i]->GetPosition()[2] << std::endl;
    }
    return world;
}


Geomlist * LoadWorld(const std::string & filename) {
    //opens the input file stream and uses FromJson to convert Json to Geomlist * -format.
    std::ifstream file(filename);
    std::stringstream ss;
    if (file){

        ss << file.rdbuf();
        file.close();
    }
    std::string a = ss.str();
    std::cout << a;
    auto j2 = json::parse(ss);
    std::cout<<"received json file: "<<j2.dump()<<std::endl;
    return FromJson(j2);

}

