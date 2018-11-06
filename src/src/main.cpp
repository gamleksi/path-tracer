#include <iostream>
#include "../include/vec3.h"
#include "../include/ray.h"
/*
 *  test function for ray
 *  linearly blends white and blue depending on the
 *  up/downess of the y coordinate.
 *  step 1 creates an unit vector -1 < y < 1
 *  step 2 scaling to 0 < t < 1
 *  when t = 1 return blue, when t = 0 return white
 *  blend in between
 */
vec3<float> color(const ray& r)
{
    vec3<float> unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction[1] + 1.0);
    float diff = (1.0 - t);
    return vec3<float>(1.0, 1.0, 1.0) * diff + vec3<float>(0.5, 0.7, 1.0) * t;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    vec3<float> v1(1.0, 2.0, 3.0);
    vec3<float> v2(1.5, 2.5, 34.0);
    vec3<float> v3 =  v2;
    auto v4 = v1 + v2;
    auto v5 = v1 - v2;
    auto v6 = v1 * v2;
    auto v7 = v1 / v2;

    float a = 3.0;
    auto v8 = v1 / a;
    auto v9 = v1 - a;
    auto v10 = v1 +  a;
    auto v11 = v1 * a;

//    auto v8 = v1;
//    auto v9 =  a - v1;
//    auto v10 = v1 +  a;
//    auto v11 = v1 * a;

    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;
    std::cout << v4 << std::endl;

    return 0;
}