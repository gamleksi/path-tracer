//
// Created by Jan Lundström on 08/12/2018.
//

#ifndef PATH_TRACER_TEXTURE_H
#define PATH_TRACER_TEXTURE_H


#include <memory>
#include <vector/vec3.h>
#include <camera/camera.h>
#include "perlin.h"

/*
 * Textures bring scene to life. Constant texture works as "solid color" and returns chosen color when hit by Ray.
 */
class Texture {
public:
    // u & v are texture mapping coordinates used with image textures
    virtual vec3<float> Value(float u, float v, const vec3<float>& p) const = 0;
};


/*
 * Constant solid color texture
 */
class ConstantTexture : public Texture {
public:
    ConstantTexture() {}
    ConstantTexture(vec3<float> c) : color(c) {};

    virtual vec3<float> Value(float u, float v, const vec3<float>& p) const {
        return color;
    }

private:
    vec3<float> color;
};


/*
 * CheckerTexture creates chess board style pattern
 */
class CheckerTexture : public Texture {
public:
    CheckerTexture() {}
    CheckerTexture(std::shared_ptr<Texture> t0, std::shared_ptr<Texture> t1, int s): even(t0), odd(t1), size(s) {}

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

/*
 * PerlinTexture creates white to black noise.
 */
class PerlinTexture : public Texture {

public:

    // Gives float between 0 and 1, creates grey colors
    PerlinTexture() {}
    PerlinTexture(float sc) : scale(sc) {}
    virtual vec3<float> Value(float u, float v, const vec3<float>& p) const {
        return vec3<float>(1,1,1)*noise.Noise(p);
    }
private:
    Perlin noise;
    float scale;
};

#endif //PATH_TRACER_TEXTURE_H
