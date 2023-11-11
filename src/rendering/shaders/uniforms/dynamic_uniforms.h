// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  3/11/2023

#ifndef ZPG_DYNAMIC_UNIFORMS_H
#define ZPG_DYNAMIC_UNIFORMS_H

#include <array>
#include <memory>
#include <stdexcept>
#include "../../../models/properties/material.h"
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
    // lights locations
    SHADER_UNIFORM_LOCATION point_num_loc = -1;
    std::array<SHADER_UNIFORM_LOCATION, (POINT_CONFIG.max_count * POINT_CONFIG.parameter_count)> point_loc = {};

    SHADER_UNIFORM_LOCATION directional_num_loc = -1;
    std::array<SHADER_UNIFORM_LOCATION, (DIRECTIONAL_CONFIG.max_count *
                                         DIRECTIONAL_CONFIG.parameter_count)> directional_loc = {};

    SHADER_UNIFORM_LOCATION spotlight_num_loc = -1;
    std::array<SHADER_UNIFORM_LOCATION, (SPOTLIGHT_CONFIG.max_count *
                                         SPOTLIGHT_CONFIG.parameter_count)> spotlight_loc = {};

    // material locations
    SHADER_UNIFORM_LOCATION material_struct_loc = -1;
    std::array<SHADER_UNIFORM_LOCATION, 4> material_loc = {};
private:
    // lights cache
    ShaderUniform<std::shared_ptr<std::vector<std::shared_ptr<Light>>>> lights_collection;
    // material cache
    ShaderUniform<Material*> material;
private:
    static void setUniforms(const LightProperty* properties, size_t size,
                     const GLint* locations);
    static bool lightCheck(const char* name, int count, int max_count, SHADER_UNIFORM_LOCATION location);

    void lazyPassLights();
    void lazyPassMaterial();
public:
    bool update(const EventArgs& event_args);
    void lazyPassUniforms();
};


#endif //ZPG_DYNAMIC_UNIFORMS_H
