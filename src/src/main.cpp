#include <iostream>
#include <memory>
#include <vector>
#include "vector/vec3.h"
#include "ray/ray.h"
#include "geometry/geometry.h"
#include "material/material.h"
#include "camera/camera.h"
#include <chrono>
#include <SFML/Graphics/Image.hpp>
#include <omp.h>
#include <boost/program_options.hpp>
#include <iostream>

#include "geometry/sphere.h"
#include "geometry/box.h"
#include "geometry/bv_node.h"
#include "geometry/geomlist.h"

typedef std::chrono::high_resolution_clock Clock;

void GetRandomObjectList(unsigned int amount, std::vector<std::shared_ptr<Geometry>> &object_list) {
    auto num = int(sqrt(amount) / 2);

    vec3<float> odd = vec3<float>(0.2, 0.3, 0.1);
    vec3<float> even = vec3<float>(0.9, 0.9, 0.9);
    int checker_size = 10;
    std::shared_ptr<ConstantTexture> even_texture;
    even_texture = std::make_shared<ConstantTexture>(even);
    std::shared_ptr<ConstantTexture> odd_texture;
    odd_texture = std::make_shared<ConstantTexture>(odd);

    std::shared_ptr<CheckerTexture> checker;
    checker = std::make_shared<CheckerTexture>(odd_texture, even_texture, checker_size);
    std::shared_ptr<Lambertian> checker_material;
    checker_material = std::make_shared<Lambertian>(checker);

    vec3<float> mat_vec(0.5, 0.5, 0.5);
    std::shared_ptr<Material> material;
    material = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(mat_vec));

    std::shared_ptr<Sphere> floor_sphere =
            std::make_shared<Sphere>(vec3<float>(0, -1000, 0), 1000, checker_material);

    object_list.push_back(floor_sphere);
    std::vector<std::shared_ptr<Geometry>> li;

    unsigned int i = 1;
    for (int a = -num; a < num; a++) {
        for (int b = -num; b < num; b++) {
            float choose_mat = drand48();
            vec3<float> object_coord(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
            if ((object_coord - vec3<float>(4, 0.2, 0)).Norm2() > 0.9) {
                if (choose_mat < 0.8) {// Do a diffuse material
                    vec3<float> mat_vec(drand48() * drand48(), drand48() * drand48(), drand48() * drand48());
                    material = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(mat_vec));
                    li.push_back(std::make_shared<Sphere>(object_coord, 0.2, material));
                    i++;
                } else {// Do a metal material
                    vec3<float> mat_vec(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48()));
                    material = std::make_shared<Metal>(mat_vec, 0.5);
                    li.push_back(std::make_shared<Sphere>(object_coord, 0.2, material));
                    i++;
                }
            }
        }
    }

    vec3<float> odd1 = vec3<float>(0.2, 0.3, 0.1);
    vec3<float> even1 = vec3<float>(0.9, 0.2, 0.2);
    int checker_size1 = 15;
    std::shared_ptr<ConstantTexture> even_texture1;
    even_texture1 = std::make_shared<ConstantTexture>(even1);
    std::shared_ptr<ConstantTexture> odd_texture1;
    odd_texture1 = std::make_shared<ConstantTexture>(odd1);

    std::shared_ptr<CheckerTexture> checker1;
    checker1 = std::make_shared<CheckerTexture>(odd_texture1, even_texture1, checker_size1);
    std::shared_ptr<Lambertian> checker_material1;
    checker_material1 = std::make_shared<Lambertian>(checker1);

    std::shared_ptr<Material> metal_material;
    metal_material = std::make_shared<Metal>(vec3<float>(0.7,0.6,0.5),0);
    li.push_back(std::make_shared<Sphere>(vec3<float>(4,1,0), 1.0, metal_material));
    li.push_back(std::make_shared<Sphere>(vec3<float>(-4, 1, 0), 1.0, checker_material1));

    auto bb_world = std::make_shared<BoundingVolumeNode>(BoundingVolumeNode(li, 0.0, 1.0));
    object_list.push_back(bb_world);

}

void CornellBoxScene(std::vector<std::shared_ptr<Geometry>> &object_list) {

    // Light
    vec3<float> light_vec(4, 4, 4);
    std::shared_ptr<Material> light;
    light = std::make_shared<DiffuseLight>(std::make_shared<ConstantTexture>(light_vec));

    // Colors
    vec3<float> grey(0.3, 0.3, 0.3);
    vec3<float> red(0.7, 0.05, 0.05);
    vec3<float> green(0.1, 0.5, 0.1);
    vec3<float> copper(0.72,0.45,0.2);
    vec3<float> white(0.9,0.9,0.9);

    // Materials
    std::shared_ptr<Material> grey_material;
    std::shared_ptr<Material> red_material;
    std::shared_ptr<Material> green_material;
    std::shared_ptr<Material> glass_material;
    std::shared_ptr<Material> metal_material;
    std::shared_ptr<Material> white_material;
    grey_material = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(grey));
    red_material = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(red));
    green_material = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(green));
    glass_material = std::make_shared<Dielectric>(1.5);
    //metal_material = std::make_shared<Metal>(std::make_shared<Constant_texture>(copper), 0.5);
    metal_material = std::make_shared<Metal>(copper, 0);
    white_material = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(white));


    // Green
    std::shared_ptr<YzRect> green_rect;
    green_rect = std::make_shared<YzRect>(0, 555, 0, 555, 0, green_material);

    // Red
    std::shared_ptr<YzRect> red_rect;
    red_rect = std::make_shared<YzRect>(0, 555, 0, 555, 555, red_material);
    std::shared_ptr<FlipNormals> flipped_red = std::make_shared<FlipNormals>(red_rect);

    // Light
    std::shared_ptr<XzRect> light_source;
    light_source = std::make_shared<XzRect>(200, 555-200, 200, 555-200, 553, light);

    // Ceiling
    std::shared_ptr<XzRect> ceiling_rect;
    ceiling_rect = std::make_shared<XzRect>(0, 555, 0, 555, 555, grey_material);
    std::shared_ptr<FlipNormals> flipped_ceiling = std::make_shared<FlipNormals>(ceiling_rect);

    // Floor
    std::shared_ptr<XzRect> floor_rect;
    floor_rect = std::make_shared<XzRect>(0, 555, 0, 555, 0, metal_material);

    // Back wall
    std::shared_ptr<XyRect> wall_rect;
    wall_rect = std::make_shared<XyRect>(0, 555, 0, 555, 555, grey_material);
    std::shared_ptr<FlipNormals> flipped_wall = std::make_shared<FlipNormals>(wall_rect);

    // Sphere 1
    std::shared_ptr<Sphere> sphere;
    sphere = std::make_shared<Sphere>(vec3<float>(70,60,400), 60, white_material);

    // Sphere 2
    std::shared_ptr<Sphere> sphere2;
    sphere2 = std::make_shared<Sphere>(vec3<float>(400,100, 350), 100, metal_material);


    // Sphere 3 kupu ulko
    std::shared_ptr<Sphere> sphere3;
    sphere3 = std::make_shared<Sphere>(vec3<float>(200,110, 200), 110, glass_material);

    // Sphere 4 kupu sisä
    std::shared_ptr<Sphere> sphere4;
    sphere4 = std::make_shared<Sphere>(vec3<float>(200,110, 200), -100, glass_material);

    // World
    std::vector<std::shared_ptr<Geometry>> li;

    object_list.push_back(sphere);
    object_list.push_back(sphere2);
    object_list.push_back(flipped_red);
    object_list.push_back(green_rect);
    object_list.push_back(light_source);
    object_list.push_back(floor_rect);
    object_list.push_back(flipped_ceiling);
    object_list.push_back(flipped_wall);
}


void Render(const int nx, const int ny, sf::Uint8 (*pixels)[3], const std::shared_ptr<Geometry> &world, const Camera cam,
            unsigned int ns, const bool normal, const bool day_light) {

    std::cout << "Rendering.." << std::endl;
#pragma omp parallel
    {

#pragma omp for schedule(static, 1)
        for (int j = 0; j < ny; j++) {
            for (int i = 0; i < nx; i++) {
                vec3<float> col(0, 0, 0);
                for (int s = 0; s < ns; s++) {
                    float u = 1 - float(i + drand48()) / float(nx);
                    float v = 1 - float(j + drand48()) / float(ny);
                    const ray<float> r = cam.GetRay(u, v);
                    if (normal) {
                        col += NormalMapping(r, world);
                    } else if (day_light){
                        col += DayLight(r, world, 0);
                    }
                    else {
                        col += Color(r, world, 0);
                    }
                }

                col /= float(ns);
                col = vec3<float>(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
                auto ir = sf::Uint8(255.99 * col[0]);
                auto ig = sf::Uint8(255.99 * col[1]);
                auto ib = sf::Uint8(255.99 * col[2]);

                // RGB format
                pixels[j * nx + i][0] = ir;
                pixels[j * nx + i][1] = ig;
                pixels[j * nx + i][2] = ib;
            }
        }
    }
    std::cout << "Done!" << std::endl;
}

sf::Image CreateImage(int nx, int ny, sf::Uint8 (*pixels)[3]) {
    sf::Image image;
    image.create(nx, ny);
    for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
            sf::Color color(pixels[j * nx + i][0], pixels[j * nx + i][1], pixels[j * nx + i][2]);
            image.setPixel(i, j, color);
        }
    }
    return image;
}

void SaveImage(const sf::Image& image, std::string& save_to) {

    image.saveToFile(save_to);
}


int main(int argc, const char *argv[]) {
       // Environment and Rendering parameters
     int nx = 500;
     int ny = 500;

     unsigned int antialias_samples = 600;
     unsigned int number_of_objects = 10;

     bool normal_mapping = false;
     bool day_light = false;
     std::string image_path = "image.png";

     bool random_scene = false;

      try
      {
          boost::program_options::options_description desc{"Options"};
          desc.add_options()
              ("help,h", "Help screen")
              ("width", boost::program_options::value<int>()->default_value(nx), "Image width.")
              ("height", boost::program_options::value<int>()->default_value(ny), "Image height.")
              ("normal-mapping,n", boost::program_options::value<bool>()->default_value(normal_mapping), "Produces a normal mapping of the scene.")
              ("threads", boost::program_options::value<int>(), "The number of threads used. If not defined, the path tracer utilizes full the capicity of your computer cpu capacity.")
              ("samples,s", boost::program_options::value<unsigned int>()->default_value(antialias_samples), "The number of samples for each pixel.")
              ("save-to,f", boost::program_options::value<std::string>()->default_value(image_path), "File is saved to.")
              ("random,r", boost::program_options::value<bool>()->default_value(random_scene), "Introduces the random scene. If false the cornell box scene is used.")
              ("num-objects,o", boost::program_options::value<unsigned int>()->default_value(number_of_objects), "The number of objects in the random scene. This parameter only applies for the random scene.")
              ("fov", boost::program_options::value<float>(), "Horizontal field of view");

          boost::program_options::variables_map vm;
          store(parse_command_line(argc, argv, desc), vm);
          notify(vm);

          if (vm.count("help")) {
              std::cout << desc << '\n';
              exit(1);
          } else {
            if (vm.count("width")) {
                nx = vm["width"].as<int>();
                std::cout << "Image width: " << nx << std::endl;
            }
            if (vm.count("height")) {
                ny = vm["height"].as<int>();
                std::cout << "Image height: " << ny << std::endl;
            }
            if (vm.count("samples")) {
                antialias_samples = vm["samples"].as<unsigned int>();
            }
            if (vm.count("normal-mapping")) {
                normal_mapping = vm["normal-mapping"].as<bool>();
            }
            if (vm.count("threads")) {
                int threads = vm["threads"].as<int>();
                omp_set_num_threads(threads);
            }
            if (vm.count("save-to")) {

              image_path = vm["save-to"].as<std::string>();
              if(image_path.substr(image_path.length() - 4) != ".png") {
                image_path = image_path + ".png";
                std::cout << "SMLF reads only .png formats. Your image is saved to " << image_path << std::endl;
              }
            }
            if (vm.count("random")) {
              random_scene = vm["random"].as<bool>();
            }
            if (vm.count("num-objects")) {
              number_of_objects = vm["num-objects"].as<unsigned int>();
            }
          }
      }
      catch (const boost::program_options::error &ex)
      {
          std::cerr << ex.what() << std::endl;
      }

      vec3<float> look_from{};
      vec3<float> look_at{};
      float dist_to_focus = 5.0; //(look_from - look_at).Norm2();
      float aperture = 0.0;
      float fov;
      float aspect = float(nx) / float(ny);;

      if (random_scene) {
        look_from = vec3<float>(13, 2, 3);
        look_at = vec3<float>(0, 0, 0);
        fov = 20;
        aspect = float(nx) / float(ny);
      } else {
         look_from = vec3<float>(278, 278, -800);
         look_at = vec3<float>(278, 278, 0);
         fov = 40;
     }

     Camera camera(look_from, look_at, vec3<float>(0, 1, 0), fov, aspect, aperture, dist_to_focus);

     std::vector<std::shared_ptr<Geometry>> object_list;
     if (random_scene) {
       GetRandomObjectList(number_of_objects, object_list);
       day_light = true;
     } else {
       CornellBoxScene(object_list);
     }

     auto world = std::make_shared<Geomlist>(object_list);

     const auto t0 = Clock::now();
     sf::Uint8 pixels[ny * nx][3];
     Render(nx, ny, pixels, world, camera, antialias_samples, normal_mapping, day_light);
     const auto t1 = Clock::now();

     auto rendering_duration = std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count();
     std::cout << "Rendering Duration: "
               << rendering_duration
               << " seconds" << std::endl;
     sf::Image image =  CreateImage(nx, ny, pixels);
     SaveImage(image, image_path);
}