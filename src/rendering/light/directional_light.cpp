// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  3/11/2023

#include "directional_light.h"

std::array<LightProperty, 3> DirectionalLight::getParameters() const {
    return {
            LightProperty(&direction),
            LightProperty(&color),
            LightProperty(&intensity)
    };
}