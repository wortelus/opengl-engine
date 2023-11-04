//
// Created by wortelus on 3.11.23.
//

#include "dynamic_uniforms.h"

bool DynamicUniforms::update(const EventArgs& event_args) {
    switch (event_args.type) {
        case EventType::U_LIGHTS: {
            const auto* lights = static_cast<const EventPayload<std::shared_ptr<std::vector<std::shared_ptr<Light>>>>*>(&event_args);
            this->lights_collection.value = std::move(lights->getPayload());
            this->lights_collection.is_dirty = true;
        }
        default:
            return false;
    }
}

void DynamicUniforms::lazyPassUniforms() {
    if (!lights_collection.is_dirty)
        return;

    GLint point_light_num = 0;
    GLint directional_light_num = 0;
    GLint spotlight_num = 0;
    for (const auto& light: *lights_collection.value) {
        if (auto* point_light = dynamic_cast<PointLight*>(light.get())) {
            setUniforms(point_light->getParameters(),
                        point_loc.data() + (POINT_CONFIG.parameter_count * point_light_num));
            point_light_num++;
            continue;
        } else if (auto* directional_light = dynamic_cast<DirectionalLight*>(light.get())) {
            setUniforms(directional_light->getParameters(),
                        directional_loc.data() + (DIRECTIONAL_CONFIG.parameter_count * directional_light_num));
            directional_light_num++;
            continue;
        } else if (auto* spotlight = dynamic_cast<Spotlight*>(light.get())) {
            setUniforms(spotlight->getParameters(),
                        spotlight_loc.data() + (SPOTLIGHT_CONFIG.parameter_count * spotlight_num));
            spotlight_num++;
            continue;
        }
    }

    Uniforms::passUniform1i(point_num_loc, point_light_num);
    Uniforms::passUniform1i(directional_num_loc, directional_light_num);
    Uniforms::passUniform1i(spotlight_num_loc, spotlight_num);
    lights_collection.is_dirty = false;
}

void DynamicUniforms::setUniforms(const std::vector<std::tuple<std::string, LightProperty>>& properties,
                                  const GLint* locations) {
    for (size_t i = 0; i < properties.size(); ++i) {
        const auto& [name, prop] = properties[i];
        GLint loc = locations[i];
        std::visit(Uniforms(loc), prop);
    }
}

bool DynamicUniforms::lightCheck(const char* name, const int count, const int max_count,
                                 const SHADER_UNIFORM_LOCATION location) {
    if (count > max_count) {
        printf("Too many %s in scene. Max is %d.\n", name, max_count);
        return false;
    }
    if (location == -1) {
        printf("Disabling %s for this scene...\n", name);
        return false;
    }
    return true;
}
