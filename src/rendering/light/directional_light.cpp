// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  3/11/2023

#include "directional_light.h"

constexpr std::array<const char*, 3> DirectionalLight::getParameterNames() {
    return std::array<const char*, 3>{
            "direction",
            "color",
            "intensity"
    };
}

std::vector<std::tuple<std::string, LightProperty>> DirectionalLight::getParameters() const {
    return {
            std::make_tuple("direction", LightProperty(&direction)),
            std::make_tuple("color", LightProperty(&color)),
            std::make_tuple("intensity", LightProperty(&intensity))
    };
}