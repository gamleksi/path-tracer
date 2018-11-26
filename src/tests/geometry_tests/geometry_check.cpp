#include <iostream>
#include <cmath>
#include "gtest/gtest.h"
#include "vector/vec3.h"
#include "ray/ray.h"
#include "geometry/geometry.h"

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

TEST(GEOMETRY_TEST, SPHERE){
    Sphere *a = new Sphere(vec3<float>(0,0,-1), 0.5);
    EXPECT_EQ(0, a->GetPosition()[0]);
    EXPECT_EQ(0, a->GetPosition()[1]);
    EXPECT_EQ(-1, a->GetPosition()[2]);
    EXPECT_EQ(0.5, a->GetRadius());
    delete a;

}

TEST(GEOMETRY_TEST, GEOMLIST){
    Geometry *li[3]; //pointer to array of 3 Geometries
    li[0] = new Sphere(vec3<float>(0,0,-1), 0.5); //placing Spheres to Geometry array
    li[1] = new Sphere(vec3<float>(0,-100.5,-1),100);
    li[2] = new Sphere(vec3<float>(0,-0.5,-1),2);
    Geomlist * world = new Geomlist(li,3); // constructing Geometry list with array.


    EXPECT_EQ(3,world->GetObjectNum());
    EXPECT_EQ(0,world->GetObjects()[0]->GetPosition()[0]);
    EXPECT_EQ(-1,world->GetObjects()[0]->GetPosition()[2]);
    EXPECT_EQ(-100.5,world->GetObjects()[1]->GetPosition()[1]);
    EXPECT_EQ(-1,world->GetObjects()[1]->GetPosition()[2]);
    EXPECT_EQ(2,world->GetObjects()[2]->GetRadius());

    delete li[2];
    delete li[1];
    delete li[0];

}