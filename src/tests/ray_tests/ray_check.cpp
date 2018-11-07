#include <iostream>
#include <cmath>
#include "gtest/gtest.h"
#include "vector/vec3.h"
#include "ray.h"

TEST(ray_test, origin_test)
{
    vec3<float> v1(1.0, 2.0, 3.0);
    vec3<float> v2(0.5, 4.0, 6.0);
    ray<float> ray1(v1, v2);

    vec3<float> v3 = ray1.origin();
    EXPECT_EQ(v1[0], v3[0]);
    EXPECT_EQ(v1[1], v3[1]);
    EXPECT_EQ(v1[2], v3[2]);
}
TEST(ray_test, direction_test)
{
    vec3<float> v1(1.0, 2.0, 3.0);
    vec3<float> v2(0.5, 4.0, 6.0);
    ray<float> ray1(v1, v2);

    vec3<float> v4 = ray1.direction();
    EXPECT_EQ(v2[0], v4[0]);
    EXPECT_EQ(v2[1], v4[1]);
    EXPECT_EQ(v2[2], v4[2]);
}

