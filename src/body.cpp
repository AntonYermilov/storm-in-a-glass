#include <cmath>

#include "configuration.h"
#include "liquid.h"
#include "body.h"

#include <iostream>

#define EPSILON 1e-5
#define sqr(x) ((x) * (x))
#define sgn(x) ((x) > 0 ? 1 : -1)

body_t::body_t(float radius, float density, float position_x, float position_y) :
        radius(radius), density(density), position_x(position_x), position_y(position_y) {
    area = M_PI * sqr(radius);
    weight = area * density;

    speed = 0.0f;
    acceleration = 0.0f;
}

void body_t::update(const configuration_t& config, const liquid_t& liquid, float time_delta) {
    float area_under_liquid = get_area_under_liquid(liquid);
    float area_over_liquid = get_area_over_liquid(liquid);
    float middel_area = get_middel_area(liquid);

    float buoyant_force = liquid.liquid_density * config.gravity * area_under_liquid;
    float resistance_force = 0.47 * middel_area * liquid.liquid_density * sqr(speed) * sgn(speed) / 2.0f;
    float result_force = weight * config.gravity - buoyant_force - resistance_force;
    
    acceleration = result_force / weight;
    position_y -= speed * time_delta + acceleration * sqr(time_delta) / 2.0f;
    speed += acceleration * time_delta;

    if (position_y < radius + EPSILON) {
        position_y = radius;
        speed = 0.0f;
    }
}

float body_t::get_area_under_liquid(const liquid_t& liquid) const {
    float depth = liquid.liquid_level - position_y;
    if (fabsf(depth) > radius - EPSILON) {
        return depth > 0.0f ? area : 0.0f;
    }

    float angle = acosf(depth / radius);
    return area * (1.0f - angle / M_PI) + depth * radius * sinf(angle);
}

float body_t::get_area_over_liquid(const liquid_t& liquid) const {
    return area - get_area_under_liquid(liquid);
}

float body_t::get_middel_area(const liquid_t& liquid) const {
    if (speed > 0.0f) {
        if (position_y < liquid.liquid_level + EPSILON) {
            return 2.0f * radius;
        }
        if (position_y > liquid.liquid_level + radius - EPSILON) {
            return 0.0f;
        }

        float distance = position_y - liquid.liquid_level;
        return 2.0f * sqrtf(sqr(radius) - sqr(distance));
    } else {
        if (position_y > liquid.liquid_level - EPSILON) {
            return 0.0f;
        }
        if (position_y < liquid.liquid_level - radius + EPSILON) {
            return 2.0f * radius;
        }
        
        float depth = liquid.liquid_level - position_y;
        return 2.0f * radius - 2.0f * sqrtf(sqr(radius) - sqr(depth));
    }
}

float body_t::get_radius() const {
    return radius;
}

float body_t::get_density() const {
    return density;
}

float body_t::get_position_x() const {
    return position_x;
}

float body_t::get_position_y() const {
    return position_y;
}

