#include <iostream>
#include <vector>
#include "vector/vec3.h"
#include "ray/ray.h"
#include "geometry/geometry.h"
#include "material/material.h"
#include "camera/camera.h"
#include <opencv2/highgui/highgui.hpp>
#include <chrono>
#include <omp.h>

typedef std::chrono::high_resolution_clock Clock;


void GetRandomObjectList(unsigned int amount, std::vector<std::shared_ptr<Geometry>> &li) {

    //Checker colors
    vec3<float> odd = vec3<float>(0.5, 0.3, 0.1);
    vec3<float> even = vec3<float>(0.9, 0.9, 0.9);
    int checker_size = 50;

    std::shared_ptr<Constant_texture> odd_texture;
    odd_texture = std::make_shared<Constant_texture>(odd);

    std::shared_ptr<Constant_texture> even_texture;
    even_texture = std::make_shared<Constant_texture>(even);

    std::shared_ptr<Checker_texture> checker;
    checker = std::make_shared<Checker_texture>(odd_texture, even_texture, checker_size);

    std::shared_ptr<Lambertian> checker_material;
    checker_material = std::make_shared<Lambertian>(checker);

    vec3<float> mat_vec(drand48(), drand48(), drand48());
    std::shared_ptr<Sphere> floor_sphere =
            std::make_shared<Sphere>(vec3<float>(0, -1005, -1), 1000, checker_material);

    li.push_back(floor_sphere);

    for (unsigned int i = 1; i < amount; i++) {

        auto x = 20.0 * drand48() - 5;
        auto y = -5.0 * drand48();
        auto z = -10 * drand48();
        vec3<float> object_coord(x, y, z);
        float radius = 2.0 * drand48();

        vec3<float> mat_vec(drand48(), drand48(), drand48());
        std::shared_ptr<Material> material;

        if (drand48() < 0.5) {
            material = std::make_shared<Metal>(std::make_shared<Constant_texture>(mat_vec));
        } else {
            material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(mat_vec));
        }
        li.push_back(std::make_shared<Sphere>(object_coord, radius, material));
    }
}

void GetDebugObjectList(unsigned int amount, std::vector<std::shared_ptr<Geometry>>& object_list) {

  float y_step = 9;
  float x_step = 10;

  unsigned int layers = 8;

  int columns = amount / layers;

  vec3<float> mat_vec(0.5, 0.5, 0.5);
  std::shared_ptr<Material> material;
  material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(mat_vec));

  std::shared_ptr<Sphere> floor_sphere =
      std::make_shared<Sphere>(vec3<float>(0, -1000, 0), 1000, material);

  object_list.push_back(floor_sphere);

  std::vector<std::shared_ptr<Geometry>> random_objects;

  for (unsigned int j = 0; j < layers; j++) {

    auto y = -100.0 + j * y_step;

    for (unsigned int i = 0; i < columns; i++) {

      float radius = 3;
      auto x = -80 + x_step * i;
      auto z = -50;  // + 10 * drand48();
      vec3<float> object_coord(x, y, z);

      vec3<float> mat_vec(drand48(), drand48(), drand48());
      std::shared_ptr<Material> material;

      if (drand48() < 0.5) {
          material = std::make_shared<Metal>(std::make_shared<Constant_texture>(mat_vec));
      } else {
          material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(mat_vec));
      }
      random_objects.push_back(std::make_shared<Sphere>(object_coord, radius, material));
    }
  }
  auto bb_world = std::make_shared<BoundingVolumeNode>(BoundingVolumeNode(random_objects, 0.0, 1.0));
  object_list.push_back(bb_world);
}

void Render(const int nx, const int ny, uchar (*image)[3], const std::shared_ptr<Geometry> &world, const Camera cam, unsigned int ns) {

    std::cout << "Rendering.." << std::endl;
    #pragma omp parallel
    {

    #pragma omp for schedule(static,1)
    for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
            vec3<float> col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = 1 - float(i + drand48()) / float(nx);
                float v = 1 - float(j + drand48()) / float(ny);
                const ray<float> r = cam.GetRay(u, v);
                col += Color(r, world, 0);
            }

            col /= float(ns);
            col = vec3<float>(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            auto ir = uchar(255.99 * col[0]);
            auto ig = uchar(255.99 * col[1]);
            auto ib = uchar(255.99 * col[2]);

            // BGR format
            image[j * nx + i][0] = ib;
            image[j * nx + i][1] = ig;
            image[j * nx + i][2] = ir;
        }
    }
    }
    std::cout << "Done!" << std::endl;
}

void ShowImage(int nx, int ny, uchar (*image)[3]) {
    cv::Mat rgb_mat(ny, nx, CV_8UC3, image);
    cv::imshow("Image is shown!", rgb_mat);
    cv::waitKey(0);
}

void SaveImage(int nx, int ny, uchar (*image)[3], std::string save_to) {
    cv::Mat rgb_mat(ny, nx, CV_8UC3, image);
    cv::imwrite(save_to, rgb_mat);
}

int main() {

  // Environment and Rendering parameters
  int nx = 800;
  int ny = 400;
  unsigned int antialias_samples = 50;
  unsigned int number_of_objects = 80;

/**
 * In order to get everything out of your computer the number of threads should be dividable by 8 and nx * ny % num_threads == 0
 * Based on couple of experiments the number of threads should be the number of cores in your computer.
 * You can check how well the path tracer is utilizing your computer with htop command in terminal.
 * If you don't have it, brew install htop.
 */

  int num_threads = 8;
  omp_set_num_threads(num_threads);

  // Create Camera

  vec3<float> look_from(0, 0, 0);
  vec3<float> look_at(0, 0, -1);
  float dist_to_focus = (look_from - look_at).Norm2();
  float aperture = 0.0;
  float fov = 90;
  float aspect = float(nx) / float(ny);

  Camera camera(look_from, look_at, vec3<float>(0, 1, 0), fov, aspect, aperture, dist_to_focus);

  std::vector<std::shared_ptr<Geometry>> object_list;
  GetDebugObjectList(number_of_objects, object_list);

  auto world = std::make_shared<Geomlist>(object_list);

  // Rendering bounding box
  const auto t0 = Clock::now();

  uchar bb_image[ny * nx][3];
  Render(nx, ny, bb_image, world, camera, antialias_samples);
  const auto t1 = Clock::now();

  auto bb_rendering_duration = std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count();
  std::cout << "Bounding Box Rendering Duration: "
          << bb_rendering_duration
          << " secondds" << std::endl;

  SaveImage(nx, ny, bb_image, "../awd_image.jpg"); // TODO: fix path

}