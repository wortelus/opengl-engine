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
#include "../../../util/const_lights.h"

class DynamicUniforms {
public:
    SHADER_UNIFORM_LOCATION point_num_loc = -1;
    std::array<SHADER_UNIFORM_LOCATION, (POINT_CONFIG.max_count * POINT_CONFIG.parameter_count)> point_loc = {};

    SHADER_UNIFORM_LOCATION directional_num_loc = -1;
    std::array<SHADER_UNIFORM_LOCATION, (DIRECTIONAL_CONFIG.max_count * DIRECTIONAL_CONFIG.parameter_count)> directional_loc = {};

    SHADER_UNIFORM_LOCATION spotlight_num_loc = -1;
    std::array<SHADER_UNIFORM_LOCATION, (SPOTLIGHT_CONFIG.max_count * SPOTLIGHT_CONFIG.parameter_count)> spotlight_loc = {};
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
