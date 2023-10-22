// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  16/10/2023

#include "light.h"

void Light::setUniforms(Shader *shader, const std::string& prefix) const {
    shader->passUniform3fv(prefix + ".position", this->position);
    shader->passUniform3fv(prefix + ".color", this->color);
    shader->passUniform1f(prefix + ".intensity", this->intensity);
}

void PhongLight::setUniforms(Shader *shader, const std::string &prefix) const {
    Light::setUniforms(shader, prefix);
    shader->passUniform1f(prefix + ".constant", this->attenuation.constant);
    shader->passUniform1f(prefix + ".linear", this->attenuation.linear);
    shader->passUniform1f(prefix + ".quadratic", this->attenuation.quadratic);
}
