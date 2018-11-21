#include <iostream>
#include <vector>
#include "vector/vec3.h"
#include "ray/ray.h"
#include <opencv2/highgui/highgui.hpp>
#include "geometry/geometry.h"
#include "camera/camera.h"

int main() {

    int nx = 800;
    int ny = 400;
    int ns = 20;//determines how many rays are sent through a pixel for antialiasing

    uchar image[ny][nx][3];

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    Geometry *li[3];
    li[0] = new Sphere(vec3<float>(0,0,-1), 0.5);
    li[1] = new Sphere(vec3<float>(0,-100.5,-1),100);
    li[2] = new Sphere(vec3<float>(0,-0.5,-1),0.5);

    Geometry * world = new Geomlist(li,3);
    Camera cam(90, float(nx)/float(ny));

    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            vec3<float> col(0, 0, 0);
            for(int s=0; s < ns; s++)
            {
                float u = 1 - float(i + drand48()) / float(nx);
                float v = 1 - float(j + drand48()) / float(ny);
                ray<float> r = cam.GetRay(u, v);
                col += Color(r, world);
            }
            //averages the colors of rays going through a pixel
            col /= float(ns);
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