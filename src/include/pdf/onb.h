//
// Created by Jan Lundström on 2018-12-11.
//

#ifndef PATH_TRACER_ONB_H
#define PATH_TRACER_ONB_H

#include <vector/vec3.h>

class Onb {
public:
    Onb() {}

    inline vec3<float> operator[](int i) const { return axis[i]; }

    vec3<float> u() const { return axis[0]; }

    vec3<float> v() const { return axis[1]; }

    vec3<float> w() const { return axis[2]; }

    vec3<float> Local(float a, float b, float c) const { return a * u() + b * v() + c * w(); }

    vec3<float> Local(const vec3<float> &a) const { return a[0] * u() + a[1] * v() + a[2] * w(); }

    void Build_from_w(const vec3<float> &n) {
        axis[2] = n.Unit();
        vec3<float> a;
        if (fabs(w()[0]) > 0.9)
            a = vec3<float>(0, 1, 0);
        else
            a = vec3<float>(1, 0, 0);
        axis[1] = Cross(w(), a).Turn_unit();
        axis[0] = Cross(w(), v());
    }



    vec3<float> axis[3];


};




#endif //PATH_TRACER_ONB_H
