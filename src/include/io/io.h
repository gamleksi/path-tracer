//
// Created by Jesse Miettinen on 21/11/2018.
//


#ifndef PATH_TRACER_IO_H
#define PATH_TRACER_IO_H
#include <iostream>
#include <nlohmann/json.hpp>
// for convenience
using json = nlohmann::json;
#include "geometry/geometry.h"



json SaveWorld(Geomlist *world){
    json j;
    //j["pi"] = 3.141;
    for (auto i = 0; i<world->GetObjectNum();i++){
        //std::cout<<"Objectamount: "<<world->GetObjectNum()<<" i: "<< i<<std::endl;
        //std::cout<<world->GetPosition()<<std::endl;
        j["position"]["x"]= world->GetPosition()[0];
        j["position"]["y"] = world->GetPosition()[1];
        j["position"]["z"] = world->GetPosition()[2];
    }
    //for (auto& element : j) {
//        std::cout<<"!!" << element << '\n';
//    }
    return j;
};

#endif //PATH_TRACER_IO_H
