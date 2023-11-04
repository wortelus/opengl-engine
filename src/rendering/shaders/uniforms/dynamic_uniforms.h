//
// Created by wortelus on 3.11.23.
//

#ifndef ZPG_DYNAMIC_UNIFORMS_H
#define ZPG_DYNAMIC_UNIFORMS_H

#include <array>
#include <memory>
#include <stdexcept>
#include "../../../util/const.h"
#include "../../light/light.h"
#include "../../light/point_light.h"
#include "../../light/directional_light.h"
#include "../../light/spotlight.h"
#include "uniforms.h"
#include "../../../util/event_args.h"

class DynamicUniforms {
public:
    constexpr static const char* point_varname = "point_lights";
    constexpr static const char* point_num_varname = "point_lights_count";
    constexpr static const size_t point_parameter_count = sizeof(PointLight::getParameterNames()) / sizeof(char*);
    constexpr static const size_t point_num_max = 10;

    constexpr static const char* directional_varname = "directional_lights";
    constexpr static const char* directional_num_varname = "directional_lights_count";
    constexpr static const size_t directional_parameter_count =
            sizeof(DirectionalLight::getParameterNames()) / sizeof(char*);
    constexpr static const size_t directional_num_max = 5;

    constexpr static const char* spotlight_varname = "spotlights";
    constexpr static const char* spotlight_num_varname = "spotlights_count";
    constexpr static const size_t spotlight_parameter_count = sizeof(Spotlight::getParameterNames()) / sizeof(char*);
    constexpr static const size_t spotlight_num_max = 5;
public:
    SHADER_UNIFORM_LOCATION point_num_loc = -1;
    std::array<SHADER_UNIFORM_LOCATION, (point_parameter_count * point_num_max)> point_loc = {};

    SHADER_UNIFORM_LOCATION directional_num_loc = -1;
    std::array<SHADER_UNIFORM_LOCATION, (directional_parameter_count * directional_num_max)> directional_loc = {};

    SHADER_UNIFORM_LOCATION spotlight_num_loc = -1;
    std::array<SHADER_UNIFORM_LOCATION, (spotlight_parameter_count * spotlight_num_max)> spotlight_loc = {};
private:
    ShaderUniform<std::shared_ptr<std::vector<std::shared_ptr<Light>>>> lights_collection;
private:
    static void setUniforms(const std::vector<std::tuple<std::string, LightProperty>>& properties, const GLint* locations);
    static bool lightCheck(const char* name, int count, int max_count, SHADER_UNIFORM_LOCATION location);
public:
    bool update(const EventArgs& event_args);
    void lazyPassUniforms();
};


#endif //ZPG_DYNAMIC_UNIFORMS_H
