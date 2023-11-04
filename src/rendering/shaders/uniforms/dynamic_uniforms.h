//
// Created by wortelus on 3.11.23.
//

#ifndef ZPG_DYNAMIC_UNIFORMS_H
#define ZPG_DYNAMIC_UNIFORMS_H

#include <array>
#include <memory>
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
public:
    bool setDynamic(const EventArgs& event_args) {
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

    void setAllLights(const std::shared_ptr<std::vector<std::shared_ptr<Light>>>& lights) {
        lights_collection.value = lights;
        lights_collection.is_dirty = true;
    }

    void passAllLights() {
        if (!lights_collection.is_dirty) {
            return;
        }

        GLint point_light_num = 0;
        GLint directional_light_num = 0;
        GLint spotlight_num = 0;
        for (const auto& light: *lights_collection.value) {
            auto* point_light = dynamic_cast<PointLight*>(light.get());
            if (point_light) {
                std::string prefix = std::string(point_varname) + "[" + std::to_string(point_light_num) + "].";
                setPointLightUniforms(*point_light, point_light_num * point_parameter_count);
                point_light_num++;
                continue;
            }
        }

        Uniforms::passUniform1i(point_num_loc, point_light_num);
    }

    // TODO: use std::visit to getParameters() and compare performance
    void setPointLightUniforms(const PointLight& light, const size_t& starting_point) {
        glUniform3fv(point_loc[starting_point + 0], 1, glm::value_ptr(light.getPosition()));
        glUniform3fv(point_loc[starting_point + 1], 1, glm::value_ptr(light.getColor()));
        glUniform1f(point_loc[starting_point + 2], light.getIntensity());
        glUniform1f(point_loc[starting_point + 3], light.getAttenuation().constant);
        glUniform1f(point_loc[starting_point + 4], light.getAttenuation().linear);
        glUniform1f(point_loc[starting_point + 5], light.getAttenuation().quadratic);
    }

    // TODO: use std::visit to getParameters() and compare performance
    void setDirectionalLightUniforms(const DirectionalLight& light, const size_t& starting_point) {
        glUniform3fv(directional_loc[starting_point + 0], 1, glm::value_ptr(light.getDirection()));
        glUniform3fv(directional_loc[starting_point + 1], 1, glm::value_ptr(light.getColor()));
        glUniform1f(directional_loc[starting_point + 2], light.getIntensity());
    }

    // TODO: use std::visit to getParameters() and compare performance
    void setSpotlightUniforms(const Spotlight& light, const size_t& starting_point) {
        glUniform3fv(spotlight_loc[starting_point + 0], 1, glm::value_ptr(light.getPosition()));
        glUniform3fv(spotlight_loc[starting_point + 1], 1, glm::value_ptr(light.getDirection()));
        glUniform3fv(spotlight_loc[starting_point + 2], 1, glm::value_ptr(light.getColor()));
        glUniform1f(spotlight_loc[starting_point + 3], light.getIntensity());
        glUniform1f(spotlight_loc[starting_point + 4], light.getAttenuation().constant);
        glUniform1f(spotlight_loc[starting_point + 5], light.getAttenuation().linear);
        glUniform1f(spotlight_loc[starting_point + 6], light.getAttenuation().quadratic);
        glUniform1f(spotlight_loc[starting_point + 7], light.getCutoff());
        glUniform1f(spotlight_loc[starting_point + 8], light.getOuterCutoff());
    }
};


#endif //ZPG_DYNAMIC_UNIFORMS_H
