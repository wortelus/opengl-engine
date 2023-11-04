//
// Created by wortelus on 4.11.23.
//

#ifndef ZPG_CONST_LIGHTS_H
#define ZPG_CONST_LIGHTS_H

#include <cstdio>
#include "../rendering/light/point_light.h"
#include "../rendering/light/directional_light.h"
#include "../rendering/light/spotlight.h"

struct LightConfig {
    const char* collection_name;
    const char* count_name;
    const size_t parameter_count;
    const size_t max_count;
};

inline constexpr static const LightConfig POINT_CONFIG = {
        .collection_name = "point_lights",
        .count_name = "point_lights_count",
        .parameter_count = sizeof(PointLight::getParameterNames()) / sizeof(char*),
        .max_count = 10
};

inline constexpr static const LightConfig DIRECTIONAL_CONFIG = {
        .collection_name = "directional_lights",
        .count_name = "directional_lights_count",
        .parameter_count = sizeof(DirectionalLight::getParameterNames()) / sizeof(char*),
        .max_count = 5
};


inline constexpr static const LightConfig SPOTLIGHT_CONFIG = {
        .collection_name = "spotlights",
        .count_name = "spotlights_count",
        .parameter_count = sizeof(Spotlight::getParameterNames()) / sizeof(char*),
        .max_count = 5
};

#endif //ZPG_CONST_LIGHTS_H
