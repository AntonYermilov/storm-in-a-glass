#include <vector>
#include <fstream>

#include "configuration.h"
#include "liquid.h"
#include "environment.h"
#include "body.h"
#include "json.hpp"

using json = nlohmann::json;

environment_t::environment_t() {
    config = {8.0f, 15.0f, 9.81f};
    liquid = {1000.0f, 9.0f};

    elements.emplace_back(0.2f, 1000.0f, 1.0f, 7.0f);
}

environment_t::environment_t(const char * config_file) {
    std::ifstream ifs(config_file);

    json data;
    ifs >> data;

    json& config_data = data["config"];
    config = {config_data["glass_width"], config_data["glass_height"], config_data["gravity"]};
    liquid = {config_data["liquid_density"], config_data["liquid_level"]};

    for (json& element : data["elements"]) {
        elements.emplace_back(element["radius"], element["density"], element["position_x"], element["position_y"]);
    }
}

void environment_t::add_element(const body_t& element) {
    elements.push_back(element);
}

void environment_t::update(float time_delta) {
    for (auto& element : elements) {
        element.update(config, liquid, time_delta);
    }
}

const configuration_t& environment_t::get_config() const {
    return config;
}

const liquid_t& environment_t::get_liquid() const {
    return liquid;
}

const std::vector<body_t>& environment_t::get_elements() const {
    return elements;
}

