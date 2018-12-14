//
// Created by Jan Lundström on 08/12/2018.
//
#include "texture.h"
void Constant_texture::ToJson(json& j, std::string& id)const{
    j["world"][id]["material"]["texture"]["type"] = type;
    j["world"][id]["material"]["texture"]["color"]["x"] = color[0];
    j["world"][id]["material"]["texture"]["color"]["y"] = color[1];
    j["world"][id]["material"]["texture"]["color"]["z"] = color[2];
}

void Checker_texture::ToJson(json& j, std::string& id)const{
    j["world"][id]["material"]["texture"]["type"] = type;
    j["world"][id]["material"]["texture"]["size"] = size;
    // TODO: j["world"][id]["material"]["odd"] = ;
    // TODO: j["world"][id]["material"]["even"] = ;

}

void Perlin_texture::ToJson(json& j, std::string& id)const{
    j["world"][id]["material"]["texture"]["type"] = type;
    j["world"][id]["material"]["texture"]["scale"] = scale;
    // TODO: noise->ToJson(j,id);?
}