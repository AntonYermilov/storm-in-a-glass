#ifndef __BODY_H
#define __BODY_H

#include "configuration.h"
#include "liquid.h"

class body_t {
  public:
    body_t(float radius, float density, float position_x, float position_y);

    void update(const configuration_t& config, const liquid_t& liquid, float time_delta);

    float get_radius() const;
    float get_density() const;
    float get_position_x() const;
    float get_position_y() const;

  private:
    float get_area_under_liquid(const liquid_t& liquid) const;
    float get_area_over_liquid(const liquid_t& liquid) const;
    float get_middel_area(const liquid_t& liquid) const;

    float radius;
    float density;
    float position_x;
    
    float position_y;
    float speed;
    float acceleration;

    float area;
    float weight;
};

#endif

