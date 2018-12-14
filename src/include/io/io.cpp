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

// Own functions for saving and loading for camera and Geometry objects

json ToJson(std::shared_ptr<Geomlist> &world, Camera& camera){

    json j;
    std::vector<std::shared_ptr<Geometry>> list = world->GetObjects();
    int x = world->GetListSize();
    j["objnum"] = x;
    camera.ToJson(j);
    for(int i=0; i< world->GetListSize(); i++){
        std::cout<<world->GetListSize()<<std::endl;
        std::string str = "object";
        std::string s = std::to_string(i);
        str.insert(6,s);
        list[i]->ToJson(j,str);
        auto mat = list[i]->GetMaterials();
        if (mat.size()>1){
            for (int k = 0; k<mat.size();k++){
                std::string number = std::to_string(k);
                str += number;
                str+="b";
                mat[k]->ToJson(j,str);
                str.pop_back();
                str.pop_back();
            }
        }else{
            mat[0]->ToJson(j, str);
        }

    }


    std::cout<<world->NumberOfObjects()<<std::endl;



    std::string str = "Initiating Saving algorithm";

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


std::shared_ptr<XyRect> LoadXyRect(json& j,std::string& id){
    float x0,x1,y0,y1,k;
    x0=j["world"][id]["x0_"];
    x1=j["world"][id]["x1_"];
    y0=j["world"][id]["y0_"];
    y1=j["world"][id]["y1_"];
    k=j["world"][id]["k_"];

    vec3<float> grey(0.3, 0.3, 0.3);
    std::shared_ptr<Material> grey_material;
    grey_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(grey));


    std::shared_ptr<XyRect> rect;
    rect=std::make_shared<XyRect>(x0,x1,y0,y1,k,grey_material);
    return rect;
}


std::shared_ptr<XyRect> LoadBoxesXyRect(json& j,std::string& id,std::string& number){
    float x0,x1,y0,y1,k;
    x0=j["world"][id]["Content"][number]["x0_"];
    x1=j["world"][id]["Content"][number]["x1_"];
    y0=j["world"][id]["Content"][number]["y0_"];
    y1=j["world"][id]["Content"][number]["y1_"];
    k=j["world"][id]["Content"][number]["k_"];

    vec3<float> grey(0.3, 0.3, 0.3);
    std::shared_ptr<Material> grey_material;
    grey_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(grey));


    std::shared_ptr<XyRect> rect;
    rect=std::make_shared<XyRect>(x0,x1,y0,y1,k,grey_material);
    return rect;
}


std::shared_ptr<XzRect> LoadXzRect(json& j,std::string& id){
    float x0,x1,z0,z1,k;
    x0=j["world"][id]["x0_"];
    x1=j["world"][id]["x1_"];
    z0=j["world"][id]["z0_"];
    z1=j["world"][id]["z1_"];
    k=j["world"][id]["k_"];

    vec3<float> grey(0.3, 0.3, 0.3);
    std::shared_ptr<Material> grey_material;
    grey_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(grey));

    std::shared_ptr<XzRect> rect;
    rect=std::make_shared<XzRect>(x0,x1,z0,z1,k,grey_material);
    return rect;
}


std::shared_ptr<XzRect> LoadBoxesXzRect(json& j,std::string& id,std::string& number){
    float x0,x1,z0,z1,k;
    x0=j["world"][id]["Content"][number]["x0_"];
    x1=j["world"][id]["Content"][number]["x1_"];
    z0=j["world"][id]["Content"][number]["z0_"];
    z1=j["world"][id]["Content"][number]["z1_"];
    k=j["world"][id]["Content"][number]["k_"];

    vec3<float> grey(0.3, 0.3, 0.3);
    std::shared_ptr<Material> grey_material;
    grey_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(grey));

    std::shared_ptr<XzRect> rect;
    rect=std::make_shared<XzRect>(x0,x1,z0,z1,k,grey_material);
    return rect;
}

std::shared_ptr<YzRect> LoadYzRect(json& j,std::string& id){
    float y0,y1,z0,z1,k;
    y0=j["world"][id]["y0_"];
    y1=j["world"][id]["y1_"];
    z0=j["world"][id]["z0_"];
    z1=j["world"][id]["z1_"];
    k=j["world"][id]["k_"];

    vec3<float> grey(0.3, 0.3, 0.3);
    std::shared_ptr<Material> grey_material;
    grey_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(grey));

    std::shared_ptr<YzRect> rect;
    rect=std::make_shared<YzRect>(y0,y1,z0,z1,k,grey_material);
    return rect;
}


std::shared_ptr<YzRect> LoadBoxesYzRect(json& j,std::string& id, std::string &number){
    float y0,y1,z0,z1,k;
    y0=j["world"][id]["Content"][number]["y0_"];
    y1=j["world"][id]["Content"][number]["y1_"];
    z0=j["world"][id]["Content"][number]["z0_"];
    z1=j["world"][id]["Content"][number]["z1_"];
    k=j["world"][id]["Content"][number]["k_"];

    vec3<float> grey(0.3, 0.3, 0.3);
    std::shared_ptr<Material> grey_material;
    grey_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(grey));

    std::shared_ptr<YzRect> rect;
    rect=std::make_shared<YzRect>(y0,y1,z0,z1,k,grey_material);
    return rect;
}



std::shared_ptr<Sphere> LoadSphere(json& j, std::string& id){
    vec3<float> color(0.9,0.9,0.9);
    std::shared_ptr<Material> white_material;
    white_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(color));
    std::shared_ptr<Sphere> sphere;

    float X, Y, Z, radius;
//  float a,b,c;
    X = j["world"][id]["position"]["x"];
    Y = j["world"][id]["position"]["y"];
    Z = j["world"][id]["position"]["z"];
    radius = j["world"][id]["radius"];
    std::string type;
    type = j["world"][id]["material"]["texture"]["type"];

    sphere = std::make_shared<Sphere>(vec3<float>(X,Y,Z), radius, white_material);
    return sphere;
}

std::shared_ptr<Box> LoadBox(json& j,std::string& id){
    //Box(vec3<float>& p0, vec3<float> &p1, std::shared_ptr<Geomlist> g)

    float x,y,z,xmax,ymax,zmax;
    x=j["world"][id]["pmin"]["x"];
    y=j["world"][id]["pmin"]["y"];
    z=j["world"][id]["pmin"]["z"];
    xmax=j["world"][id]["pmax"]["x"];
    ymax=j["world"][id]["pmax"]["y"];
    zmax=j["world"][id]["pmax"]["z"];
    vec3<float>p0(x,y,z);
    vec3<float>p1(xmax,ymax,zmax);

    std::vector<std::shared_ptr<Geometry>> rect_list;

    for(int i = 0; i<6;i++){
        std::string number = std::to_string(i);
        if(j["world"][id]["content"][number]["type"]=="XyRect"){
            rect_list.push_back(LoadBoxesXyRect(j,id,number));
        }else if(j["world"][id]["content"][number]["type"]=="XzRect"){
            rect_list.push_back(LoadBoxesXzRect(j,id,number));
        }else if(j["world"][id]["content"][number]["type"]=="YzRect"){
            rect_list.push_back(LoadBoxesYzRect(j,id,number));
        }else{
            std::cout<<"no way Im loading a flipnormal"<<std::endl;
        }
    }
    auto rects = std::make_shared<Geomlist>(rect_list);
    std::shared_ptr<Box> box;
    box = std::make_shared<Box>(p0,p1,rects);
    return box;
}

void FromJson(const std::string& str,std::vector<std::shared_ptr<Geometry>>& object_list) {

    std::string type_sphere = "Sphere";
    std::string type_XyRect = "XyRect";
    std::string type_XzRect = "XzRect";
    std::string type_YzRect = "YzRect";
    std::string type_FlipNormal = "FlipNormal";
    std::string type_BOX = "Box";
    json j = json::parse(str);
    int x = j["objnum"];

    for (auto i = 0; i < x; i++) {

        std::string str = "object";
        std::string s = std::to_string(i);
        str.insert(6, s);
        if(j["world"][str]["type"]==type_sphere){
            auto object = LoadSphere(j, str);
            object_list.push_back(object);
        }else if(j["world"][str]["type"]==type_XyRect){
            auto object = LoadXyRect(j, str);
            object_list.push_back(object);
        }else if(j["world"][str]["type"]==type_XzRect){
            auto object = LoadXzRect(j, str);
            object_list.push_back(object);
        }
        else if(j["world"][str]["type"]==type_YzRect){
            auto object = LoadYzRect(j, str);
            object_list.push_back(object);
        }
        else if(j["world"][str]["type"]==type_BOX){
            auto object = LoadBox(j, str);
            object_list.push_back(object);
        }
    }
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