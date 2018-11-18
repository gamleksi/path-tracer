#include <iostream>
#include <vector>
#include "vector/vec3.h"
#include "ray/ray.h"
#include <opencv2/highgui/highgui.hpp>
#include "geometry/geometry.h"
#include "camera/camera.h"
vec3<float> color(const ray<float>& r, Geometry *s) {
    Hit_record rec;
    //float t = s->RayHits(r);
    if (s->RayHits(r, 0.0, MAXFLOAT, rec)) {
        return (float) 0.5 * vec3<float>(rec.normal[0] + 1, rec.normal[1] + 1, rec.normal[2] + 1);
    } else {
        vec3<float> unit_direction = r.direction().unit();
        float t = 0.5 * (unit_direction[1] + 1.0);
        return ((float) 1.0 - t) * vec3<float>(1.0, 1.0, 1.0) + t * vec3<float>(0.5, 0.7, 1.0);
    }

}
int main() {

    int nx = 400;
    int ny = 200;

    uchar image[ny][nx][3];

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    vec3<float> lower_left_corner(-2.0, -1.0, -1.0);
    vec3<float> horizontal(4.0, 0.0, 0.0);
    vec3<float> vertical(0.0, 2.0, 0.0);
    vec3<float> origin(0.0, 0.0, 0.0);

    Geometry *li[2];
    li[0] = new Sphere("abc", Matte, vec3<float>(0,0,-1), 0.5);
    li[1] = new Sphere("def", Metal, vec3<float>(0,-100.5,-1),100);
    //Sphere sphere;
    Geometry * world = new Geomlist(li,2);

    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
//            float r = float(i) / float(nx);
//            float g = float(j) / float(ny);
//            float b = 0.2;

            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray<float> r(origin, lower_left_corner + u*horizontal + v*vertical);

            vec3<float> p = r.point(2.0);
            vec3<float> col = color(r, world);

            auto ir = uchar(255.99*col[0]);
            auto ig = uchar(255.99*col[1]);
            auto ib = uchar(255.99*col[2]);

//            auto ir = uchar(255.99);
//            auto ig = uchar(255.99);
//            auto ib = uchar(255.99);
            // BRG format
            image[j][i][0] = ib;
            image[j][i][1] = ir;
            image[j][i][2] = ig;

        }
    }

    cv::Mat rgb_mat(ny, nx, CV_8UC3, &image);
    cv::imshow("Image", rgb_mat);
    cv::waitKey(0);

    return 0;
}