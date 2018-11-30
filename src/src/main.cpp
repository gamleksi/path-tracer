#include <iostream>
#include <vector>
#include "vector/vec3.h"
#include "ray/ray.h"
#include <opencv2/highgui/highgui.hpp>
#include "geometry/geometry.h"
#include "camera/camera.h"

int RandomScene(unsigned int amount, int nx, int ny, unsigned int ns)
{
    uchar image[ny][nx][3];
    Geometry *li[amount];
    li[0] = new Sphere(vec3<float>(0,-105,-1),100);
    for(unsigned int i = 1; i < amount; i++) {

        li[i] = new Sphere(vec3<float>(20 * float(drand48())-5, -5 * float(drand48()), -10 * float(drand48())), 2 * float(drand48()));
    }

    Geometry *world = new Geomlist(li, amount);
    //first three camera parameters are vectors: look_from, look_at, view_up
    Camera cam(vec3<float>(0, -3, 0), vec3<float>(7, -5, -5), vec3<float>(0, 1, 0), 90, float(nx) / float(ny));

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3<float> col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                float u = 1 - float(i + drand48()) / float(nx);
                float v = 1 - float(j + drand48()) / float(ny);
                ray<float> r = cam.GetRay(u, v);
                col += Color(r, world);
            }
            //averages the colors of rays going through a pixel
            col /= float(ns);
            auto ir = uchar(255.99 * col[0]);
            auto ig = uchar(255.99 * col[1]);
            auto ib = uchar(255.99 * col[2]);

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


int main() {

    int nx = 800;
    int ny = 400;
    unsigned int ns = 10;//determines how many rays are sent through a pixel for antialiasing
    unsigned int amount = 15; // determines how many objects do we create

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    RandomScene(amount, nx, ny, ns);

    return 0;
}