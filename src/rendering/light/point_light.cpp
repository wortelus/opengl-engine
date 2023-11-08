// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  16/10/2023

#include "point_light.h"

std::array<LightProperty, 6> PointLight::getParameters() const {
    return {
            LightProperty(&position),
            LightProperty(&color),
            LightProperty(&intensity),
            LightProperty(&attenuation.constant),
            LightProperty(&attenuation.linear),
            LightProperty(&attenuation.quadratic)
    };
}
