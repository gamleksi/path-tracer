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



void GetRandomObjectList(unsigned int amount, std::vector<std::shared_ptr<Geometry>>& li) {

  vec3<float> mat_vec(0.5, 0.5, 0.5);
  std::shared_ptr<Sphere> floor_sphere =
      std::make_shared<Sphere>(vec3<float>(0, -1000, 0), 1000, std::make_shared<Lambertian>(mat_vec));

  li.push_back(floor_sphere);
  unsigned int i = 1;
  for(int a = -11; a < 11; a++) {
      for (int b = -11; b < 11; b++) {
          //srand48(i*time(nullptr));
          float choose_mat = drand48();
          vec3<float> object_coord(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
          if ((object_coord - vec3<float>(4, 0.2, 0)).Norm2() > 0.9) {
              if (choose_mat < 0.8) {
                  vec3<float> mat_vec(drand48()*drand48(), drand48()*drand48(), drand48()*drand48());
                  li.push_back(std::make_shared<Sphere>(object_coord, 0.2, std::make_shared<Lambertian>(mat_vec)));
                  i++;
              }
              else
              {
                  vec3<float> mat_vec(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48()));
                  li.push_back(std::make_shared<Sphere>(object_coord, 0.2, std::make_shared<Metal>(mat_vec)));
                  i++;
              }
          }
      }
  }
  li.push_back(std::make_shared<Sphere>(vec3<float>(4,1,0), 1.0, std::make_shared<Metal>(vec3<float>(0.7,0.6,0.5))));
  i++;
  li.push_back(std::make_shared<Sphere>(vec3<float>(-4,1,0), 1.0, std::make_shared<Lambertian>(vec3<float>(0.4,0.2,0.1))));
  i++;
  std::cout << i << std::endl;
/*
  for (unsigned int i = 1; i < amount; i++) {
    srand48(i*time(nullptr));
    auto x = 15.0 * drand48() - 5;
    auto y = -5.0 * drand48();
    auto z = -5.0 * drand48();
    vec3<float> object_coord(x, y, z);
    float radius = 2.0 * drand48();

    vec3<float> mat_vec(drand48(), drand48(), drand48());
    std::shared_ptr<Material> material;

    if (drand48() < 0.5) {
      material =  std::make_shared<Metal>(mat_vec);
    } else {
      material = std::make_shared<Lambertian>(mat_vec);
    }
    li.push_back(std::make_shared<Sphere>(object_coord, radius, material));
  }*/
}


void Render(int nx, int ny, uchar (*image)[3], const std::shared_ptr<Geometry>& world, const Camera cam, unsigned int ns) {

  std::cout << "Rendering..." << std::endl;

  for (int j = ny - 1; j >= 0; j--) {
      for (int i = 0; i < nx; i++) {
          vec3<float> col(0, 0, 0);
          for (int s = 0; s < ns; s++) {
              float u = 1 - float(i + drand48()) / float(nx);
              float v = 1 - float(j + drand48()) / float(ny);
              const ray<float> r = cam.GetRay(u, v);
              // vec3<float> p = r.Point(2.0); TODO: I am quite sure that fixing this would solve the irregular sphere problem
              col += Color(r, world, 0);
          }

          col /= float(ns);
          col = vec3<float> (sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
          auto ir = uchar(255.99*col[0]);
          auto ig = uchar(255.99*col[1]);
          auto ib = uchar(255.99*col[2]);

          // BGR format
          image[j * nx + i][0] = ib;
          image[j * nx + i][1] = ig;
          image[j * nx + i][2] = ir;
      }
  }
  std::cout << "Rendered!" << std::endl;
}

void ShowImage(int nx, int ny, uchar (*image)[3]){
    cv::Mat rgb_mat(ny, nx, CV_8UC3, image);
    cv::imshow("Image", rgb_mat);
    std::cout << "Done." << std::endl;
    cv::waitKey(0);
}

void SaveImage(int nx, int ny, uchar (*image)[3], std::string save_to){
    cv::Mat rgb_mat(ny, nx, CV_8UC3, image);
    cv::imwrite(save_to, rgb_mat);
}

int main() {

  // Environment and Rendering parameters
  int nx = 1200;
  int ny = 600;
  unsigned int antialias_samples = 1;
  unsigned int number_of_objects = 485;

  // Create Camera
  Camera camera(vec3<float>(13, 2, 3), vec3<float>(0, 0, 0), vec3<float>(0, 1, 0), 20, float(nx) / float(ny));

  // Random Environment
  std::vector<std::shared_ptr<Geometry>> object_list;
  GetRandomObjectList(number_of_objects, object_list);

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
  auto geomlist_world = std::make_shared<Geomlist>(Geomlist(number_of_objects, object_list));
  const auto t3 = Clock::now();

  uchar geom_image[ny * nx][3];
  Render(nx, ny, geom_image, geomlist_world, camera, antialias_samples);
  const auto t4 = Clock::now();
  auto geomlist_duration = std::chrono::duration_cast<std::chrono::seconds>(t4 - t3).count();
  std::cout << "Geomlist rendering duration: "
            << geomlist_duration
            << " seconds" << std::endl;

 // ShowImage(nx, ny, geom_image);
  SaveImage(nx, ny, geom_image, "../image.jpg"); // TODO: fix path

  return 1;
}