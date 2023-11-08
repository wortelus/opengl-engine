// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  3/11/2023

#include "spotlight.h"

std::array<LightProperty, 9> Spotlight::getParameters() const {
    return {
            LightProperty(&position),
            LightProperty(&direction),
            LightProperty(&color),
            LightProperty(&intensity),
            LightProperty(&attenuation.constant),
            LightProperty(&attenuation.linear),
            LightProperty(&attenuation.quadratic),
            LightProperty(&cutoff),
            LightProperty(&outer_cutoff)
    };
}