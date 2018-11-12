#include <iostream>
#include "vector/vec3.h"
#include "ray.h"
#include <opencv2/highgui/highgui.hpp>

int main() {

    int nx = 400;
    int ny = 200;

    uchar image[ny][nx][3];

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny-1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;

            auto ir = uchar(255.99*r);
            auto ig = uchar(255.99*g);
            auto ib = uchar(255.99*b);

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
