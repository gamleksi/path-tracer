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

TEST(geometry_test, default_sphere){
    Sphere* d = new Sphere();
    EXPECT_EQ("abc", d->get_Name());
    EXPECT_NE("ABD", d->get_Name());

    EXPECT_EQ(Matte, d->get_Material());


    delete d;

}
TEST(geometry_test, n_default_sphere){
    Sphere* d = new Sphere("Im groot!", Glass, v2, 20.0);
    EXPECT_EQ("Im groot!" ,d->GetName());
    EXPECT_EQ(Glass, d->GetMaterial());
    EXPECT_EQ(0.5,d->GetPosition()[0]);
    EXPECT_EQ(4.0,d->GetPosition()[1]);
    EXPECT_EQ(6.0,d->GetPosition()[2]);
    EXPECT_EQ(20.0,d->GetRadius());

    //cloning d to a default sphere
    Sphere c =  Sphere();
    EXPECT_EQ("abc", c.get_Name());
    c = *d; //what is happening here? This is not a copy?
    EXPECT_EQ("Im groot!", c.GetName());
    EXPECT_EQ(Glass, c.GetMaterial());
    EXPECT_EQ(0.5,c.GetPosition()[0]);
    EXPECT_EQ(4.0,c.GetPosition()[1]);
    EXPECT_EQ(6.0,c.GetPosition()[2]);
    EXPECT_EQ(20.0, c.GetRadius()); //this should not work?!
    //seems like the copy works
}

//TEST(geometry_test, discriminant_analysis){
//    vec3<float> v4(0.0,0.0,0.0);
//    vec3<float> v5(1.0,0.0,0.0);
//    vec3<float> v6(1.0,1.0,0.0);
//    vec3<float> v7(20.0,20.0,0.0);
//
//    ray<float> r(v4,v5);
//    EXPECT_EQ(1.0, r.direction()[0]);
//
//    ray<float> &ref = r;
//
//    //c is centered at x=1
//    Sphere* f = new Sphere("Im groot!", Glass, v5, 20.0);
//    //should have two solutions
//    EXPECT_EQ(true, f->RayHits(ref));
//
//    //g is centered at y=1
//    Sphere* g = new Sphere("a", Metal, v6, 1.0);
//    //Should have only 1 solution
//    EXPECT_EQ(true, g->RayHits(ref));
//
//    //h is centered at (x =20, y = 20)
//    Sphere* h = new Sphere("h", Matte, v7, 0.1);
//    EXPECT_EQ(false, h->RayHits(ref));
//
//
//}



//MagicDragon* mdragon = new MagicDragon("Puff", 976, 20);