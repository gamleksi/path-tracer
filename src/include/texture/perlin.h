/*
//
// Created by Jan Lundström on 08/12/2018.
//

#ifndef PATH_TRACER_PERLIN_H
#define PATH_TRACER_PERLIN_H


#include <vector/vec3.h>

class Perlin {
public:
    //float Noise(const vec3<float>& p) const;
    float Noise(const vec3<float> &p) const {
        float u = p[0] - floor(p[0]);
        float v = p[1] - floor(p[1]);
        float w = p[2] - floor(p[2]);
        int i = int(4*p[0]) & 255;
        int j = int(4*p[1]) & 255;
        int k = int(4*p[2]) & 255;

        return ranfloat.get()[perm_x.get()[i]^ perm_y.get()[j] ^perm_z.get()[k]];
    }

private:
    static std::shared_ptr<float> ranfloat;
    static std::shared_ptr<int> perm_x;
    static std::shared_ptr<int> perm_y;
    static std::shared_ptr<int> perm_z;};


std::shared_ptr<float> Perlin_generate() {
    std::shared_ptr<float> p = std::make_shared<float>(256);
    for (int i = 0; i < 256; ++i) {
        p.get()[i] = drand48();
    }
    return p;
}

void Permute(std::shared_ptr<int> p, int n) {
    for (int i = n-1; i>0; i--) {
        int target = int(drand48()*i+1);
        int tmp = p.get()[i];
        p.get()[i] = p.get()[target];
        p.get()[target] = tmp;
    }
    return;
}


std::shared_ptr<int> Perlin_generate_perm() {
    std::shared_ptr<int> p = std::make_shared<int>(256);
    for (int i= 0; i < 256; i++) {
        p.get()[i] = i;
    }
    Permute(p, 256);
    return p;
}

// Generate noise
std::shared_ptr<float> Perlin::ranfloat = Perlin_generate();
std::shared_ptr<int> Perlin::perm_x = Perlin_generate_perm();
std::shared_ptr<int> Perlin::perm_y = Perlin_generate_perm();
std::shared_ptr<int> Perlin::perm_z = Perlin_generate_perm();


#endif //PATH_TRACER_PERLIN_H
*/
