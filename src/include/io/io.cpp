//
// Created by Jesse Miettinen on 28/11/2018.
//
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
// for convenience
using json = nlohmann::json;
#include "geometry/geometry.h"


json SaveWorld(Geomlist *world){
    json j;
    json j2;
    //j["pi"] = 3.141;
    Geometry ** objects = world->GetObjects();
    for (auto i = 0; i<world->GetObjectNum();i++){
        //std::cout<<"Objectamount: "<<world->GetObjectNum()<<" i: "<< i<<std::endl;
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

void LoadWorld(json& j){
    std::cout << j << std::endl;
    std::cout <<"j.dump()" <<j.dump()<<std::endl;
    int x = j["objnum"];
    x += 1;
    Geometry *li[x];
    for (auto i = 0; i < x; i++){
        std::cout << i << std::endl;
        float a,b,c,radius;

        std::string str ="object";
        std::string s = std::to_string(i+1);
        str.insert(6,s);
        std::cout<<str<<"!"<<std::endl;

        a = j["world"][str]["x"];
        std::cout<<a;
        b = j["world"][str]["y"];
        std::cout<<b;
        c = j["world"][str]["z"];
        std::cout<<c;
        radius = j["world"][str]["radius"];
        li[i] = new Sphere(vec3<float>(a,b,c),radius);
    }
//  Geomlist * world = new Geomlist(li,3);
//  Geometry ** objects = world->GetObjects();
//  for (auto i = 0; i<world->GetObjectNum();i++){
//      std::cout << i << objects[i]->GetPosition()[0]<< " ";
//      std::cout << i << objects[i]->GetPosition()[1]<< " ";
//      std::cout << i << objects[i]->GetPosition()[2]<< std::endl;
//  }
}