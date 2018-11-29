#include <iostream>
#include <vector>
#include "vector/vec3.h"
#include "ray/ray.h"
#include "geometry/geometry.h"
#include "material/material.h"
#include "camera/camera.h"
#include <opencv2/highgui/highgui.hpp>

int main() {

    int nx = 400;
    int ny = 200;
    int ns = 20; // antialising

    uchar image[ny][nx][3];

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    Geometry *li[4];

    li[0] = new Sphere(vec3<float>(0.5,0.5,-1), 0.3, new Lambertian(vec3<float>(0.8,0.3,0.3)));
    li[1] = new Sphere(vec3<float>(0,-100.5,-1),100, new Lambertian(vec3<float>(0.8,0.3,0.3)));
    li[2] = new Sphere(vec3<float>(0,-0.5,-1),0.5, new Metal(vec3<float>(0.8,0.3,0.3)));
    li[3] = new Sphere(vec3<float>(3,2,0),0.1, new Metal(vec3<float>(0.4,0.3,0.3)));

    Geometry* world = new Geomlist(li,4);
    Camera cam;

    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3<float> col(0,0,0);
            for (int s=0; s < ns; s++) {
                float u = 1 - float(i+ drand48()) / float(nx);
                float v = 1 - float(j+ drand48()) / float(ny);
                ray<float> r = cam.GetRay(u, v);
                vec3<float> p = r.Point(2.0);
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
    cv::waitKey(0);

    return 0;
}