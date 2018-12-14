
//
// Created by Jan Lundström on 08/12/2018.
//

#ifndef PATH_TRACER_PERLIN_H
#define PATH_TRACER_PERLIN_H


#include <vector/vec3.h>
#include <vector>
#include <nlohmann/json.hpp>
// for convenience
using json = nlohmann::json;

class Perlin {
public:

    void Permute(std::vector<int> p, int n) {
        for (int i = n - 1; i > 0; i--) {
            int target = int(drand48() * i + 1);
            int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
        return;
    }


    std::vector<float> Perlin_generate() {
        std::vector<float> p(256);
        for (int i = 0; i < 256; ++i) {
            p[i] = (float)drand48();
        }
        return p;
    }

    std::vector<int> Perlin_generate_perm() {
        std::vector<int> p(256);
        for (int i = 0; i < 256; i++) {
            p[i] = i;
        }
        Perlin::Permute(p, 256);
        return p;
    }

    float Noise(const vec3<float> &p) const {
        float u = p[0] - floor(p[0]);
        float v = p[1] - floor(p[1]);
        float w = p[2] - floor(p[2]);
        int i = int(4*p[0] ) & 255;
        int j = int(4*p[1] ) & 255;
        int k = int(4*p[2] ) & 255;
        return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
    }
    // TODO: void ToJson(json& j, std::string & id);?

private:
    std::vector<float> ranfloat = Perlin_generate();
    std::vector<int> perm_x = Perlin_generate_perm();
    std::vector<int> perm_y = Perlin_generate_perm();
    std::vector<int> perm_z = Perlin_generate_perm();
};

#endif //PATH_TRACER_PERLIN_H

