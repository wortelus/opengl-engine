// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  3/11/2023

#include "spotlight.h"

constexpr std::array<const char*, 9> Spotlight::getParameterNames() {
    return std::array<const char*, 9>{
            "position",
            "direction",
            "color",
            "intensity",
            "constant",
            "linear",
            "quadratic",
            "cutoff",
            "outer_cutoff"
    };
}

std::vector<std::tuple<std::string, LightProperty>> Spotlight::getParameters() const {
    return {
            std::make_tuple("position", LightProperty(&position)),
            std::make_tuple("direction", LightProperty(&direction)),
            std::make_tuple("color", LightProperty(&color)),
            std::make_tuple("intensity", LightProperty(&intensity)),
            std::make_tuple("constant", LightProperty(&attenuation.constant)),
            std::make_tuple("linear", LightProperty(&attenuation.linear)),
            std::make_tuple("quadratic", LightProperty(&attenuation.quadratic)),
            std::make_tuple("cutoff", LightProperty(&cutoff)),
            std::make_tuple("outer_cutoff", LightProperty(&outer_cutoff))
    };
}