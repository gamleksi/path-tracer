#include <iostream>
#include <cmath>
#include "gtest/gtest.h"
#include "vector/vec3.h"
#include "ray.h"
//#include "geometry/geometry.hpp"

vec3<float> v1 = vec3<float>(1.0, 2.0, 3.0);
vec3<float> v2(0.5, 4.0, 6.0);

TEST(geometry_test, hello) {

    auto v3 = v1;

    EXPECT_EQ(v1[0], v3[0]);
    EXPECT_EQ(v1[1], v3[1]);
    EXPECT_EQ(v1[2], v3[2]);

    v3 = v2;
    EXPECT_EQ(v2[0], v3[0]);
    EXPECT_EQ(v2[1], v3[1]);
    EXPECT_EQ(v2[2], v3[2]);
}
