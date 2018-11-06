#include <iostream>
#include "vector/vec3.h"

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