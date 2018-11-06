//
// Created by Aleksi Hämäläinen on 06/11/2018.
//

//#include "gtest/gtest.h"
//
//TEST(vector_test, test_1) {
//    EXPECT_EQ(1, 0);
//}

#include <iostream>
#include <cmath>
#include "gtest/gtest.h"
#include "vector/vec3.h"

vec3<float> v1 = vec3<float>(1.0, 2.0, 3.0);
vec3<float> v2(0.5, 4.0, 6.0);


TEST(vector_test, vector_copy) {

    auto v3 = v1;

    EXPECT_EQ(v1[0], v3[0]);
    EXPECT_EQ(v1[1], v3[1]);
    EXPECT_EQ(v1[2], v3[2]);

    v3 = v2;
    EXPECT_EQ(v2[0], v3[0]);
    EXPECT_EQ(v2[1], v3[1]);
    EXPECT_EQ(v2[2], v3[2]);

}

TEST(vector_test, vector_algebra) {

    auto v3 = v1 + v2;

    EXPECT_EQ(v3[0], v1[0] + v2[0]);
    EXPECT_EQ(v3[1], v1[1] + v2[1]);
    EXPECT_EQ(v3[2], v1[2] + v2[2]);

    v3 = v1 - v2;

    EXPECT_EQ(v3[0], v1[0] - v2[0]);
    EXPECT_EQ(v3[1], v1[1] - v2[1]);
    EXPECT_EQ(v3[2], v1[2] - v2[2]);

    v3 = v1 * v2;

    EXPECT_EQ(v3[0], v1[0] * v2[0]);
    EXPECT_EQ(v3[1], v1[1] * v2[1]);
    EXPECT_EQ(v3[2], v1[2] * v2[2]);

    v3 = v1 / v2;

    EXPECT_EQ(v3[0], v1[0] / v2[0]);
    EXPECT_EQ(v3[1], v1[1] / v2[1]);
    EXPECT_EQ(v3[2], v1[2] / v2[2]);

    v3 = -v1;

    EXPECT_EQ(v3[0], -v1[0]);
    EXPECT_EQ(v3[1], -v1[1]);
    EXPECT_EQ(v3[2], -v1[2]);

    v3 = +v1;

    EXPECT_EQ(v3[0], v1[0]);
    EXPECT_EQ(v3[1], v1[1]);
    EXPECT_EQ(v3[2], v1[2]);

    // cross product
    float c = cross(v1, v2);
    EXPECT_EQ(v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2], c);

    float b = v1.norm2();
    EXPECT_EQ(std::sqrt(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]), b);
}

TEST(vector_test, vector_operations) {

    auto v3 = v1;
    v3 += v2;

    EXPECT_EQ(v3[0], v1[0] + v2[0]);
    EXPECT_EQ(v3[1], v1[1] + v2[1]);
    EXPECT_EQ(v3[2], v1[2] + v2[2]);

    v3 = v1;
    v3 -= v2;

    EXPECT_EQ(v3[0], v1[0] - v2[0]);
    EXPECT_EQ(v3[1], v1[1] - v2[1]);
    EXPECT_EQ(v3[2], v1[2] - v2[2]);

    v3 = v1;
    v3 *= v2;

    EXPECT_EQ(v3[0], v1[0] * v2[0]);
    EXPECT_EQ(v3[1], v1[1] * v2[1]);
    EXPECT_EQ(v3[2], v1[2] * v2[2]);

    v3 = v1;
    v3 /= v2;

    EXPECT_EQ(v3[0], v1[0] / v2[0]);
    EXPECT_EQ(v3[1], v1[1] / v2[1]);
    EXPECT_EQ(v3[2], v1[2] / v2[2]);
}


TEST(vector_test, scalar_vector) {

    float a = 4.0;
    auto v3 = a + v1;

    EXPECT_EQ(v3[0], a + v1[0]);
    EXPECT_EQ(v3[1], a + v1[1]);
    EXPECT_EQ(v3[2], a + v1[2]);

    v3 = v1 + a;

    EXPECT_EQ(v3[0], a + v1[0]);
    EXPECT_EQ(v3[1], a + v1[1]);
    EXPECT_EQ(v3[2], a + v1[2]);

    v3 = a - v1;

    EXPECT_EQ(v3[0], a - v1[0]);
    EXPECT_EQ(v3[1], a - v1[1]);
    EXPECT_EQ(v3[2], a - v1[2]);

    v3 = v1 - a;

    EXPECT_EQ(v3[0], v1[0] - a);
    EXPECT_EQ(v3[1], v1[1] - a);
    EXPECT_EQ(v3[2], v1[2] - a);

    v3 = a * v1;

    EXPECT_EQ(v3[0], a * v1[0]);
    EXPECT_EQ(v3[1], a * v1[1]);
    EXPECT_EQ(v3[2], a * v1[2]);

    v3 = v1 * a;

    EXPECT_EQ(v3[0], a * v1[0]);
    EXPECT_EQ(v3[1], a * v1[1]);
    EXPECT_EQ(v3[2], a * v1[2]);

    v3 = v1 / a;

    EXPECT_EQ(v3[0], v1[0] / a);
    EXPECT_EQ(v3[1], v1[1] / a);
    EXPECT_EQ(v3[2], v1[2] / a);

}


