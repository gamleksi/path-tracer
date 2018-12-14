//
// Created by Jan Lundström on 08/12/2018.
//

#include <stdlib.h>
#include "perlin.h"
#include "vector/vec3.h"





//float Perlin::Noise(const vec3<float> &p) const {
//    float u = p[0] - floor(p[0]);
//    float v = p[1] - floor(p[1]);
//    float w = p[2] - floor(p[2]);
//    int i = floor(p[0]);
//    int j = floor(p[1]);
//    int k = floor(p[2]);
//    vec3<float> c[2][2][2];
//    for (int di=0; di < 2; di++) {
//        for (int dj=0; dj < 2; dj++) {
//            for (int dk=0; dk < 2; dk++) {
//                c[di][dj][dk] = ranvec[perm_x[(i+di) & 255] ^ perm_y[(j+dj) & 255] ^ perm_z[(k+dk) & 255]];
//            }
//        }
//    }
//
//    return Perlin::Perlin_interpolation(c,u,v,w);
//}



