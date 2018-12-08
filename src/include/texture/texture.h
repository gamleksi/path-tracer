//
// Created by Jan Lundström on 08/12/2018.
//

#ifndef PATH_TRACER_TEXTURE_H
#define PATH_TRACER_TEXTURE_H


#include <vector/vec3.h>
#include <camera/camera.h>

class Texture {
public:
    virtual vec3<float> Value(float u, float v, const vec3<float>& p) const = 0;
};



class Constant_texture : public Texture {
public:
    Constant_texture() {}
    Constant_texture(vec3<float> c) : color(c) {};

    virtual vec3<float> Value(float u, float v, const vec3<float>& p) const {
        return color;
    }

private:
    vec3<float> color;
};


class Checker_texture : public Texture {
public:
    Checker_texture() {}
    Checker_texture(std::shared_ptr<Texture> t0, std::shared_ptr<Texture> t1, int s): even(t0), odd(t1), size(s) {}

    virtual vec3<float> Value(float u, float v, const vec3<float>& p) const {
        float sines = sin(size*p[0]) * sin(size*p[1]) * sin(size*p[2]);
        if (sines < 0)
            return odd->Value(u,v,p);
        else
            return even->Value(u,v,p);
    }

private:
    std::shared_ptr<Texture> odd;
    std::shared_ptr<Texture> even;
    int size;
};


#endif //PATH_TRACER_TEXTURE_H
