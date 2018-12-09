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

  vec3<float> mat_vec(drand48(), drand48(), drand48());
  std::shared_ptr<Sphere> floor_sphere =
      std::make_shared<Sphere>(vec3<float>(0, -105, -1), 100, std::make_shared<Metal>(mat_vec));

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
      material =  std::make_shared<Metal>(mat_vec);
    } else {
      material = std::make_shared<Lambertian>(mat_vec);
    }
    li.push_back(std::make_shared<Sphere>(object_coord, radius, material));
  }
}

void GetDebugObjectList(unsigned int amount, std::vector<std::shared_ptr<Geometry>>& li) {

  float y_step = 9;
  float x_step = 10;

  unsigned int layers = 8;

  int columns = amount / layers;

  for (unsigned int j = 0; j < layers; j++) {

    auto y = -40.0 + j * y_step;

    for (unsigned int i = 0; i < columns; i++) {

      float radius = 3;
      auto x = -80 + x_step * i;
      auto z = -50;  // + 10 * drand48();
      vec3<float> object_coord(x, y, z);

      vec3<float> mat_vec(drand48(), drand48(), drand48());
      std::shared_ptr<Material> material;

      if (drand48() < 0.5) {
        material = std::make_shared<Metal>(mat_vec);
      } else {
        material = std::make_shared<Lambertian>(mat_vec);
      }
      li.push_back(std::make_shared<Sphere>(object_coord, radius, material));
    }
  }
}

void Render(int nx, int ny, uchar (*image)[3], const std::shared_ptr<Geometry>& world, const Camera cam, unsigned int ns) {

  std::cout << "Rendering..." << std::endl;

  for (int j = ny - 1; j >= 0; j--) {
      for (int i = 0; i < nx; i++) {
          vec3<float> col(0, 0, 0);
          for (int s = 0; s < ns; s++) {
              auto u = 1 - float(i + drand48()) / float(nx);
              auto v = 1 - float(j + drand48()) / float(ny);
              const auto r = cam.GetRay(u, v);
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
  std::cout << "Rendred!" << std::endl;
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
  int nx = 400;
  int ny = 200;
  unsigned int antialias_samples = 3;
  unsigned int number_of_objects = 160;

// Random Environment

//  vec3<float> look_from(0, -3, 0);
//  vec3<float> look_at(7, -5, -5);
//  float dist_to_focus = (look_from - look_at).Norm2();
//  std::cout << dist_to_focus << std::endl;
//  float aperture = 2.0;
//  float fov = 90;
//  float aspect = float(nx) / float(ny);
//
//  Camera camera(look_from, look_at, vec3<float>(0, 1, 0), fov,
//      aspect);
//
//  std::vector<std::shared_ptr<Geometry>> object_list;
//  GetRandomObjectList(number_of_objects, object_list);

  // Debug Environment

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
  // GetRandomObjectList(number_of_objects, object_list);

//  FOR the future..

  auto bb_world = std::make_shared<BoundingVolumeNode>(BoundingVolumeNode(object_list, 0.0, 100.0));
  std::cout << "The Number of objects in total " << bb_world->NumberOfObjects() << std::endl;
  std::cout << "The Number on left " << bb_world->NumberOfLeftObjects() << std::endl;
  std::cout << "The Number on right " << bb_world->NumberOfRightObjects() << std::endl;
  // Rendering bounding box
  const auto t0 = Clock::now();

  uchar bb_image[ny * nx][3];
  Render(nx, ny, bb_image, bb_world, camera, antialias_samples);
  const auto t1 = Clock::now();

  auto bb_rendering_duration = std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count();
  std::cout << "Bounding Box Rendering Duration: "
          << bb_rendering_duration
          << " secondds" << std::endl;

  SaveImage(nx, ny, bb_image, "../bb_image.jpg"); // TODO: fix path

 //  Geomlist world

  auto geomlist_world = std::make_shared<Geomlist>(Geomlist(number_of_objects, object_list));
  const auto t3 = Clock::now();
  uchar geom_image[ny * nx][3];
  Render(nx, ny, geom_image, geomlist_world, camera, antialias_samples);
  const auto t4 = Clock::now();
  auto geomlist_duration = std::chrono::duration_cast<std::chrono::seconds>(t4 - t3).count();
  std::cout << "Geomlist rendering duration: "
            << geomlist_duration
            << " secondds" << std::endl;
 // ShowImage(nx, ny, geom_image);
  SaveImage(nx, ny, geom_image, "../image.jpg"); // TODO: fix path

  return 1;
}