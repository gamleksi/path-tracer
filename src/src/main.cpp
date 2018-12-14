#include <iostream>
#include <vector>
#include "vector/vec3.h"
#include "ray/ray.h"
#include "geometry/geometry.h"
#include "material/material.h"
#include "camera/camera.h"
#include <chrono>
#include <SFML/Graphics/Image.hpp>

typedef std::chrono::high_resolution_clock Clock;

#include <omp.h>

//void GetRandomObjectList(unsigned int amount, std::vector<std::shared_ptr<Geometry>> &object_list) {
//    int num = int(sqrt(amount) / 2);
//
//    vec3<float> mat_vec(0.5, 0.5, 0.5);
//    vec3<float> light_vec(4, 4, 4);
//    std::shared_ptr<Material> material;
//    material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(mat_vec));
//    //material = std::make_shared<DiffuseLight>(std::make_shared<Constant_texture>(light_vec));
//
//    std::shared_ptr<Sphere> floor_sphere =
//            std::make_shared<Sphere>(vec3<float>(0, -1000, 0), 200, material); //default radius 1000
//
//    object_list.push_back(floor_sphere);
//
//    std::vector<std::shared_ptr<Geometry>> li;
//
//    std::shared_ptr<Material> light;
//    light = std::make_shared<DiffuseLight>(std::make_shared<Constant_texture>(light_vec));
//    std::shared_ptr<XyRect> light_rect = std::make_shared<XyRect>(-2.0, 3.0, 0.0, 1.0, 4, light);
//    li.push_back(light_rect);
//    std::shared_ptr<XyRect> light_rect2 = std::make_shared<XyRect>(1.0, 6.0, 0.5, 6.0, -4.0, light);
//    li.push_back(light_rect2);
//
//    unsigned int i = 1;
//    for (int a = -num; a < num; a++) {
//        for (int b = -num; b < num; b++) {
//            float choose_mat = drand48();
//            vec3<float> object_coord(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
//            if ((object_coord - vec3<float>(4, 0.2, 0)).Norm2() > 0.9) {
//                if (choose_mat < 0.8) {
//                    vec3<float> mat_vec(drand48() * drand48(), drand48() * drand48(), drand48() * drand48());
//                    material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(mat_vec));
//                    li.push_back(std::make_shared<Sphere>(object_coord, 0.2, material));
//                    i++;
//                } else {
//                    vec3<float> mat_vec(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48()));
//                    material = std::make_shared<Metal>(std::make_shared<Constant_texture>(mat_vec), 0.5);
//                    li.push_back(std::make_shared<Sphere>(object_coord, 0.2, material));
//                    i++;
//                }
//            }
//        }
//    }
//    //Checker colors
//    vec3<float> odd = vec3<float>(0.5, 0.3, 0.1);
//    vec3<float> even = vec3<float>(0.9, 0.9, 0.9);
//    int checker_size = 3;
//    std::shared_ptr<Constant_texture> even_texture;
//    even_texture = std::make_shared<Constant_texture>(even);
//    std::shared_ptr<Constant_texture> odd_texture;
//    odd_texture = std::make_shared<Constant_texture>(odd);
//
//    std::shared_ptr<Checker_texture> checker;
//    checker = std::make_shared<Checker_texture>(odd_texture, even_texture, checker_size);
//    std::shared_ptr<Lambertian> checker_material;
//    checker_material = std::make_shared<Lambertian>(checker);
//
//    //std::shared_ptr<Material> metal_material;
//    //metal_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(vec3<float>(0.7,0.6,0.5)));
//    //li.push_back(std::make_shared<Sphere>(vec3<float>(4,1,0), 1.0, metal_material));
//    i++;
//    li.push_back(std::make_shared<Sphere>(vec3<float>(-4, 1, 0), 1.0, checker_material));
//    //li.push_back(std::make_shared<Sphere>(vec3<float>(-4,1,0), 1.0, std::make_shared<Lambertian>(vec3<float>(0.4,0.2,0.1))));
//    i++;
//
//    //playing with boxes
//    std::shared_ptr<Box> kuutio = std::make_shared<Box>(vec3<float>(4, 1, 0), vec3<float>(5, 2, 1), light);
//    li.push_back(kuutio);
//
//    auto bb_world = std::make_shared<BoundingVolumeNode>(BoundingVolumeNode(li, 0.0, 1.0));
//    object_list.push_back(bb_world);
//
//}
////
////
//////can be modified, does not work with current camera settings
////void GetDebugObjectList(unsigned int amount, std::vector<std::shared_ptr<Geometry>> &object_list) {
////
////    float y_step = 9;
////    float x_step = 10;
////
////    unsigned int layers = 8;
////
////    int columns = amount / layers;
////
////    vec3<float> mat_vec(0.5, 0.5, 0.5);
////    std::shared_ptr<Material> material;
////    material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(mat_vec));
////
////    std::shared_ptr<Sphere> floor_sphere =
////            std::make_shared<Sphere>(vec3<float>(0, -1000, 0), 1000, material);
////
////    object_list.push_back(floor_sphere);
////
////    std::vector<std::shared_ptr<Geometry>> random_objects;
////
////    for (unsigned int j = 0; j < layers; j++) {
////
////        auto y = -100.0 + j * y_step;
////
////        for (unsigned int i = 0; i < columns; i++) {
////
////            float radius = 3;
////            auto x = -80 + x_step * i;
////            auto z = -50;  // + 10 * drand48();
////            vec3<float> object_coord(x, y, z);
////
////            vec3<float> mat_vec(drand48(), drand48(), drand48());
////            std::shared_ptr<Material> material;
////
////            if (drand48() < 0.5) {
////                material = std::make_shared<Metal>(std::make_shared<Constant_texture>(mat_vec), 0.5);
////            } else {
////                material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(mat_vec));
////            }
////            random_objects.push_back(std::make_shared<Sphere>(object_coord, radius, material));
////        }
////    }
////    auto bb_world = std::make_shared<BoundingVolumeNode>(BoundingVolumeNode(random_objects, 0.0, 1.0));
////    object_list.push_back(bb_world);
////}
//
//
//void CornellBoxScene(std::vector<std::shared_ptr<Geometry>> &object_list) {
//
//    // Light
//    vec3<float> light_vec(7, 7, 7);
//    std::shared_ptr<Material> light;
//    light = std::make_shared<DiffuseLight>(std::make_shared<Constant_texture>(light_vec));
//
//    // Colors
//    vec3<float> grey(0.3, 0.3, 0.3);
//    vec3<float> red(0.7, 0.05, 0.05);
//    vec3<float> green(0.1, 0.5, 0.1);
//    vec3<float> copper(0.72,0.45,0.2);
//    vec3<float> white(0.9,0.9,0.9);
//
//
//    // Materials
//    std::shared_ptr<Material> grey_material;
//    std::shared_ptr<Material> red_material;
//    std::shared_ptr<Material> green_material;
//    std::shared_ptr<Material> glass_material;
//    std::shared_ptr<Material> metal_material;
//    std::shared_ptr<Material> white_material;
//    grey_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(grey));
//    red_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(red));
//    green_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(green));
//    glass_material = std::make_shared<Dielectric>(1.5);
//    metal_material = std::make_shared<Metal>(std::make_shared<Constant_texture>(copper), 0.5);
//    white_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(white));
//
//    // Green
//    std::shared_ptr<YzRect> green_rect;
//    green_rect = std::make_shared<YzRect>(0, 555, 0, 555, 0, green_material);
//
//    // Red
//    std::shared_ptr<YzRect> red_rect;
//    red_rect = std::make_shared<YzRect>(0, 555, 0, 555, 555, red_material);
//    std::shared_ptr<FlipNormals> flipped_red = std::make_shared<FlipNormals>(red_rect);
//
//    // Light
//    std::shared_ptr<XzRect> light_source;
//    light_source = std::make_shared<XzRect>(200, 555-200, 200, 555-200, 553, light);
//
//    // Ceiling
//    std::shared_ptr<XzRect> ceiling_rect;
//    ceiling_rect = std::make_shared<XzRect>(0, 555, 0, 555, 555, grey_material);
//    std::shared_ptr<FlipNormals> flipped_ceiling = std::make_shared<FlipNormals>(ceiling_rect);
//
//    // Floor
//    std::shared_ptr<XzRect> floor_rect;
//    floor_rect = std::make_shared<XzRect>(0, 555, 0, 555, 0, grey_material);
//
//    // Back wall
//    std::shared_ptr<XyRect> wall_rect;
//    wall_rect = std::make_shared<XyRect>(0, 555, 0, 555, 555, grey_material);
//    std::shared_ptr<FlipNormals> flipped_wall = std::make_shared<FlipNormals>(wall_rect);
//
//
//    // Sphere 1
//    std::shared_ptr<Sphere> sphere;
//    sphere = std::make_shared<Sphere>(vec3<float>(70,60,400), 60, white_material);
//
//    // Sphere 2
//    std::shared_ptr<Sphere> sphere2;
//    sphere2 = std::make_shared<Sphere>(vec3<float>(400,100, 350), 100, metal_material);
//
//
//    // Sphere 3 kupu ulko
//    std::shared_ptr<Sphere> sphere3;
//    sphere3 = std::make_shared<Sphere>(vec3<float>(200,110, 200), 110, glass_material);
//
//    // Sphere 4 kupu sisä
//    std::shared_ptr<Sphere> sphere4;
//    sphere4 = std::make_shared<Sphere>(vec3<float>(200,110, 200), -100, glass_material);
//
//
//    // World
//    std::vector<std::shared_ptr<Geometry>> li;
//
//
//    object_list.push_back(sphere);
//    object_list.push_back(sphere2);
////    object_list.push_back(sphere3);
////    object_list.push_back(sphere4);
//    object_list.push_back(flipped_red);
//    object_list.push_back(green_rect);
//    object_list.push_back(light_source);
//    object_list.push_back(floor_rect);
//    object_list.push_back(flipped_ceiling);
//    object_list.push_back(flipped_wall);
//
//
//
//
//
//
////    li.push_back(flipped_red);
////    li.push_back(green_rect);
////    li.push_back(light_source);
////    li.push_back(ceiling_rect);
////    li.push_back(floor_rect);
////    li.push_back(wall_rect);
////    li.push_back(sphere);
//
//    //auto bb_world = std::make_shared<BoundingVolumeNode>(BoundingVolumeNode(li, 0.0, 1.0));
//    //object_list.push_back(bb_world);
//}
//
//
//void Render(const int nx, const int ny, uchar (*image)[3], const std::shared_ptr<Geometry> &world, const Camera cam,
//            unsigned int ns, const bool normal) {
//
//    std::cout << "Rendering.." << std::endl;
//#pragma omp parallel
//    {
//
//#pragma omp for schedule(static, 1)
//        for (int j = 0; j < ny; j++) {
//            for (int i = 0; i < nx; i++) {
//                vec3<float> col(0, 0, 0);
//                for (int s = 0; s < ns; s++) {
//                    float u = 1 - float(i + drand48()) / float(nx);
//                    float v = 1 - float(j + drand48()) / float(ny);
//                    const ray<float> r = cam.GetRay(u, v);
//                    if (normal) {
//                        col += NormalMapping(r, world);
//                    } else {
//                        col += Color(r, world, 0);
//                    }
//                }
//
//                col /= float(ns);
//                col = vec3<float>(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
//                auto ir = uchar(255.99 * col[0]);
//                auto ig = uchar(255.99 * col[1]);
//                auto ib = uchar(255.99 * col[2]);
//
//                // BGR format
//                image[j * nx + i][0] = ib;
//                image[j * nx + i][1] = ig;
//                image[j * nx + i][2] = ir;
//            }
//        }
//    }
//    std::cout << "Done!" << std::endl;
//}
//
////void ShowImage(int nx, int ny, uchar (*image)[3]) {
////    cv::Mat rgb_mat(ny, nx, CV_8UC3, image);
////    cv::imshow("Image is shown!", rgb_mat);
////    cv::waitKey(0);
////}
////
////void SaveImage(int nx, int ny, uchar (*image)[3], std::string save_to) {
////    cv::Mat rgb_mat(ny, nx, CV_8UC3, image);
////    cv::imwrite(save_to, rgb_mat);
////}
//
//int main() {
//
//    // Environment and Rendering parameters
//    int nx = 500;
//    int ny = 500;
//
//    unsigned int antialias_samples = 2;
//    unsigned int number_of_objects = 10;
//
//    bool normal_mapping = true;
//
///**
// * In order to get everything out of your computer the number of threads should be dividable by 8 and nx * ny % num_threads == 0
// * Based on couple of experiments the number of threads should be the number of cores in your computer.
// * You can check how well the path tracer is utilizing your computer with htop command in terminal.
// * If you don't have it, brew install htop.
// */
//
//    int num_threads = 8;
//    omp_set_num_threads(num_threads);
//
//    // Default Camera Settings
//    vec3<float> look_from(278, 278, -800);
//    vec3<float> look_at(278, 278, 0);
//    float dist_to_focus = 5.0;//(look_from - look_at).Norm2();
//    float aperture = 0.0;
//    float fov = 40;
//    float aspect = float(nx) / float(ny);
//
//    Camera camera(look_from, look_at, vec3<float>(0, 1, 0), fov, aspect, aperture, dist_to_focus);
//
//    std::vector<std::shared_ptr<Geometry>> object_list;
//    CornellBoxScene(object_list);
//    //GetRandomObjectList(number_of_objects, object_list);
//
//    auto world = std::make_shared<Geomlist>(object_list);
//
//    // Rendering bounding box
//    const auto t0 = Clock::now();
//
//    uchar bb_image[ny * nx][3];
//    Render(nx, ny, bb_image, world, camera, antialias_samples, normal_mapping);
//    const auto t1 = Clock::now();
//
//    auto bb_rendering_duration = std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count();
//    std::cout << "Bounding Box Rendering Duration: "
//              << bb_rendering_duration
//              << " seconds" << std::endl;
//
//    SaveImage(nx, ny, bb_image, "../image_10000.jpg"); // TODO: fix path
//    ShowImage(nx, ny, bb_image);
//
//}


int main() {

}
