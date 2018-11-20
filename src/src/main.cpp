#include <iostream>
#include <vector>
#include "vector/vec3.h"
#include "ray/ray.h"
#include <opencv2/highgui/highgui.hpp>
#include "geometry/geometry.h"
#include "camera/camera.h"

int main() {

    int nx = 400;
    int ny = 200;

    uchar image[ny][nx][3];

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    vec3<float> lower_left_corner(-2.0, -1.0, -1.0);
    vec3<float> horizontal(4.0, 0.0, 0.0);
    vec3<float> vertical(0.0, 2.0, 0.0);
    vec3<float> origin(0.0, 0.0, 0.0);

    Geometry *li[3];
    li[0] = new Sphere(vec3<float>(0,0,-1), 0.5);
    li[1] = new Sphere(vec3<float>(0,-100.5,-1),100);
    li[2] = new Sphere(vec3<float>(0,-0.5,-1),0.5);

    Geometry * world = new Geomlist(li,3);
    //camera can be fetched later from the camera class
    //Camera cam;

    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {

            float u = 1 - float(i) / float(nx);
            float v = 1 - float(j) / float(ny);
            ray<float> r(origin, lower_left_corner + u*horizontal + v*vertical);

            vec3<float> p = r.point(2.0);
            vec3<float> col = color(r, world);

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