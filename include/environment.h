#ifndef __ENVIRONMENT_H
#define __ENVIRONMENT_H

#include <vector>

#include "configuration.h"
#include "liquid.h"
#include "body.h"

class environment_t {
  public:
    environment_t();
    environment_t(const char * config_file);

    void add_element(const body_t& element);

    void update(float time_delta);

    const configuration_t& get_config() const;
    const liquid_t& get_liquid() const;
    const std::vector<body_t>& get_elements() const;

  private:
    configuration_t config;
    liquid_t liquid;
    std::vector<body_t> elements;
};

#endif

