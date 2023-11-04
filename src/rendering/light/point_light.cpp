// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  16/10/2023

#include "point_light.h"

std::vector<std::tuple<std::string, LightProperty>> PointLight::getParameters() const {
    return {
            std::make_tuple("position", LightProperty(&position)),
            std::make_tuple("color", LightProperty(&color)),
            std::make_tuple("intensity", LightProperty(&intensity)),
            std::make_tuple("constant", LightProperty(&attenuation.constant)),
            std::make_tuple("linear", LightProperty(&attenuation.linear)),
            std::make_tuple("quadratic", LightProperty(&attenuation.quadratic))
    };
}
