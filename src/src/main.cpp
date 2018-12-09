#include <iostream>
#include <vector>
#include "vector/vec3.h"
#include "ray/ray.h"
#include "geometry/geometry.h"
#include "material/material.h"
#include "camera/camera.h"
#include <opencv2/highgui/highgui.hpp>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
#include <omp.h>

int GetRandomObjectList(unsigned int amount, std::vector<std::shared_ptr<Geometry>>& li) {

  int num = int(sqrt(amount)/2);

  vec3<float> mat_vec(0.5, 0.5, 0.5);
  std::shared_ptr<Material> material;
  material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(mat_vec));

  std::shared_ptr<Sphere> floor_sphere =
      std::make_shared<Sphere>(vec3<float>(0, -1000, 0), 1000, material);
  li.push_back(floor_sphere);

  //std::shared_ptr<XyRect> test_rect = std::make_shared<XyRect>(3.0, 5.0, 1.0, 3.0, -1.0, material);
  //li.push_back(test_rect);

  unsigned int i = 1;
  for(int a = -num; a < num; a++) {
      for (int b = -num; b < num; b++)
      {
          float choose_mat = drand48();
          vec3<float> object_coord(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
          if ((object_coord - vec3<float>(4, 0.2, 0)).Norm2() > 0.9)
          {
              if (choose_mat < 0.8)
              {
                  vec3<float> mat_vec(drand48()*drand48(), drand48()*drand48(), drand48()*drand48());
                  material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(mat_vec));
                  li.push_back(std::make_shared<Sphere>(object_coord, 0.2, material));
                  i++;
              }
              else
              {
                  vec3<float> mat_vec(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48()));
                  material = std::make_shared<Metal>(std::make_shared<Constant_texture>(mat_vec));
                  li.push_back(std::make_shared<Sphere>(object_coord, 0.2, material));
                  i++;
              }
          }
      }
  }
  //Checker colors
  vec3<float> odd = vec3<float>(0.5, 0.3, 0.1);
  vec3<float> even = vec3<float>(0.9, 0.9, 0.9);
  int checker_size = 50;
  std::shared_ptr<Constant_texture> even_texture;
  even_texture = std::make_shared<Constant_texture>(even);
  std::shared_ptr<Constant_texture> odd_texture;
  odd_texture = std::make_shared<Constant_texture>(odd);

  std::shared_ptr<Checker_texture> checker;
  checker = std::make_shared<Checker_texture>(odd_texture, even_texture, checker_size);
  std::shared_ptr<Lambertian> checker_material;
  checker_material = std::make_shared<Lambertian>(checker);

  std::shared_ptr<Material> metal_material;
  metal_material = std::make_shared<Lambertian>(std::make_shared<Constant_texture>(vec3<float>(0.7,0.6,0.5)));
  li.push_back(std::make_shared<Sphere>(vec3<float>(4,1,0), 1.0, metal_material));
  i++;
  li.push_back(std::make_shared<Sphere>(vec3<float>(-4,1,0), 1.0, checker_material));
  //li.push_back(std::make_shared<Sphere>(vec3<float>(-4,1,0), 1.0, std::make_shared<Lambertian>(vec3<float>(0.4,0.2,0.1))));
  i++;
  return i;

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
    int nx = 1200;
    int ny = 600;

    unsigned int antialias_samples = 10;
    unsigned int number_of_objects = 100;

    /**
     * In order to get everything out of your computer the number of threads should be dividable by 8 and nx * ny % num_threads == 0
     * Based on couple of experiments the number of threads should be the number of cores in your computer.
     * You can check how well the path tracer is utilizing your computer with htop command in terminal.
     * If you don't have it, brew install htop.
     */

    int num_threads = 8;
    omp_set_num_threads(num_threads);

    // Create Camera
    Camera camera(vec3<float>(13, 2, 3), vec3<float>(0, 0, 0), vec3<float>(0, 1, 0), 20, float(nx) / float(ny));
    //Camera camera(vec3<float>(0, -3, 0), vec3<float>(7, -5, -5), vec3<float>(0, 1, 0), 90, float(nx) / float(ny));

    // Random Environment
    std::vector<std::shared_ptr<Geometry> > object_list;
    int created_objects = GetRandomObjectList(number_of_objects, object_list);

// FOR the future..

//  // Creating bounding box structure
//  auto bb_world = std::make_shared<BoundingVolumeNode>(BoundingVolumeNode(object_list, 0.0, 1.0));
//
//  // Rendering bounding box
//  const auto t0 = Clock::now();
//
//  uchar bb_image[ny * nx][3];
//  Render(nx, ny, bb_image, bb_world, camera, antialias_samples);
//
//  const auto t1 = Clock::now();
//
//  auto bb_rendering_duration = std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count();
//  std::cout << "Bounding Box Rendering Duration: "
//          << bb_rendering_duration
//          << " seconds" << std::endl;
//
//  ShowImage(nx, ny, bb_image);
//  SaveImage(nx, ny, bb_image, "../bb_image.jpg"); // TODO: fix path


    // Geomlist world
    auto geomlist_world = std::make_shared<Geomlist>(Geomlist(created_objects, object_list));
    const auto t3 = Clock::now();

    uchar geom_image[ny * nx][3];
    Render(nx, ny, geom_image, geomlist_world, camera, antialias_samples);
    const auto t4 = Clock::now();
    auto geomlist_duration = std::chrono::duration_cast<std::chrono::seconds>(t4 - t3).count();
    std::cout << "Geomlist rendering duration: "
              << geomlist_duration
              << " secondds" << std::endl;

    ShowImage(nx, ny, geom_image);
    // SaveImage(nx, ny, geom_image, "../image.jpg"); // TODO: fix path
}