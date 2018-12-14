//
// Created by Jan Lundström on 08/12/2018.
//
#include "texture.h"
void Constant_texture::ToJson(json& j, std::string& id)const{
    if(id.substr(id.length() - 1) == "b") {
        std::string id2 = id;
        id2.pop_back();
        size_t end = id2.length();
        std::string number = std::to_string(id2[end]);
        id2.pop_back();
        j["world"][id2]["content"][number]["material"]["texture"]["type"] = type;
        j["world"][id2]["content"][number]["material"]["texture"]["color"]["x"] = color[0];
        j["world"][id2]["content"][number]["material"]["texture"]["color"]["y"] = color[1];
        j["world"][id2]["content"][number]["material"]["texture"]["color"]["z"] = color[2];
    }else{
        j["world"][id]["material"]["texture"]["type"] = type;
        j["world"][id]["material"]["texture"]["color"]["x"] = color[0];
        j["world"][id]["material"]["texture"]["color"]["y"] = color[1];
        j["world"][id]["material"]["texture"]["color"]["z"] = color[2];
    }
}

void Checker_texture::ToJson(json& j, std::string& id)const{
    if(id.substr(id.length() - 1) == "b"){
        std::string id2 = id;
        id2.pop_back();
        size_t end = id2.length();
        std::string number = std::to_string(id2[end]);
        id2.pop_back();
        j["world"][id2]["content"][number]["material"]["texture"]["type"] = type;
        j["world"][id2]["content"][number]["material"]["texture"]["type"] = size;
    }else{
        j["world"][id]["material"]["texture"]["type"] = type;
        j["world"][id]["material"]["texture"]["size"] = size;
    }


    // TODO: j["world"][id]["material"]["odd"] = ;
    // TODO: j["world"][id]["material"]["even"] = ;

}

void Perlin_texture::ToJson(json& j, std::string& id)const{
    if(id.substr(id.length() - 1) == "b"){
        std::string id2 = id;
        id2.pop_back();
        size_t end = id2.length();
        std::string number = std::to_string(id2[end]);
        id2.pop_back();
        j["world"][id2]["content"][number]["material"]["texture"]["type"] = type;
        j["world"][id2]["content"][number]["material"]["texture"]["scale"] = scale;
    }else{
        j["world"][id]["material"]["texture"]["type"] = type;
        j["world"][id]["material"]["texture"]["scale"] = scale;
    }
    // TODO: noise->ToJson(j,id);?
}