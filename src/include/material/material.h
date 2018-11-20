//
// Created by Jan Lundström on 20/11/2018.
//

#ifndef PATH_TRACER_MATERIAL_H
#define PATH_TRACER_MATERIAL_H


#include <hitable/hitable.h>

class material {
public:
    virtual bool scatter(const ray& r_in, float t_min, float t_max, hit_record& rec) const = 0;
};


#endif //PATH_TRACER_MATERIAL_H
