#ifndef __LIQUID_H
#define __LIQUID_H

struct liquid_t {
    liquid_t(float liquid_density = 0.0f, float liquid_level = 0.0f);

    float liquid_density;
    float liquid_level;
};

#endif
