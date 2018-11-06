#include <iostream>
#include <cmath>
#include "gtest/gtest.h"
#include "vector/vec3.h"
#include "ray.h"

TEST(ray_test, example_test) {
    vec3<float> v1(1.0, 2.0, 3.0);
    vec3<float> v2(0.5, 4.0, 6.0);
    ray<float> ray1(v1, v2);
    color(ray1);
}
