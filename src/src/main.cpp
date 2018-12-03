#include <iostream>
#include <vector>
#include "vector/vec3.h"
#include "ray/ray.h"
#include "geometry/geometry.h"
#include "material/material.h"
#include "camera/camera.h"
#include <opencv2/highgui/highgui.hpp>
#include "io/io.h"



void GetRandomObjectList(unsigned int amount, std::vector<std::shared_ptr<Geometry>>& li) {

  vec3<float> mat_vec(drand48(), drand48(), drand48());
  std::shared_ptr<Sphere> floor_sphere =
      std::make_shared<Sphere>(vec3<float>(0, -105, -1), 100, std::make_shared<Metal>(mat_vec)); //this is pretty weird. T = Metal class but input is Vec3?

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



void Render(int nx, int ny, const Geomlist& geomlist, const Camera cam, unsigned int ns) {

  std::shared_ptr<Geomlist> world = std::make_shared<Geomlist>(geomlist);

  uchar image[ny][nx][3];

  std::cout << "Rendering..." << std::endl;

  for (int j = ny - 1; j >= 0; j--) {
      for (int i = 0; i < nx; i++) {
          vec3<float> col(0, 0, 0);
          for (int s = 0; s < ns; s++) {
              float u = 1 - float(i + drand48()) / float(nx);
              float v = 1 - float(j + drand48()) / float(ny);
              const ray<float> r = cam.GetRay(u, v);
              // vec3<float> p = r.Point(2.0); TODO Why do we have this here?
              col += Color(r, world, 0);
          }

          col /= float(ns);
          col = vec3<float> (sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
          auto ir = uchar(255.99*col[0]);
          auto ig = uchar(255.99*col[1]);
          auto ib = uchar(255.99*col[2]);

          // BGR format
          image[j][i][0] = ib;
          image[j][i][1] = ig;
          image[j][i][2] = ir;

      }
  }

    cv::Mat rgb_mat(ny, nx, CV_8UC3, &image);
    cv::imshow("Image", rgb_mat);
    std::cout << "Done." << std::endl;
    cv::waitKey(0);
}


void RandomScene() {
    int nx = 800;
    int ny = 400;
    unsigned int antialias_samples = 10;
    unsigned int number_of_objects = 5;

    std::vector<std::shared_ptr<Geometry>> object_list;
    GetRandomObjectList(number_of_objects, object_list);

    Camera camera(vec3<float>(0, -3, 0), vec3<float>(7, -5, -5), vec3<float>(0, 1, 0), 90, float(nx) / float(ny));

    Geomlist world(number_of_objects, object_list);

    Render(nx, ny, world, camera, antialias_samples);
    std::cout<<std::endl<<"input '1' if you want to save this scene. "<<std::endl;
    int q;
    std::cin >>q;
    if (q==1){
        std::string str = SaveWorld(world, camera);
        std::cout<<std::endl<<"The scene was saved to cmake-build-debug/ to a new file: " <<"'"<<str<<"'"<<std::endl;
    }

}


int main() {
    int q;
    std::cout<<std::endl<<"Program started.";
    std::cout<<std::endl<<"Type 0 to end program, 1 to create random scene or 2 to open scene from file.";
    std::cin>>q;
    while (q!=0){

        if (q == 1){
          RandomScene();
          std::cout<<std::endl<<"Type 0 to end program, 1 to create random scene or 2 to open scene from file.";
          std::cin>>q;

        }else{
          std::string str;
          std::cout<<std::endl<<"Give filename to load the world from."<<std::endl;
          std::cin>>str;
          Geomlist world = LoadWorld(str);
          Camera camera(vec3<float>(0, -3, 0), vec3<float>(7, -5, -5), vec3<float>(0, 1, 0), 90, float(800) / float(400));
          Render(800,400, world, camera, 10);
          std::cout<<std::endl<<"Type 0 to end program, 1 to create random scene or 2 to open scene from file.";
          std::cin>>q;
        }
    }


  //RandomScene();
  //RandomScene();
  return 0;
}