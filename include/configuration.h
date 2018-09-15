#ifndef __CONFIGURATION_H
#define __CONFIGURATION_H

struct configuration_t {
    configuration_t(float width = 0.0f, float height = 0.0f, float gravity = 0.0f);

    float width;
    float height;
    float gravity;
};

#endif
