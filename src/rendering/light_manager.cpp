// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  22/10/2023

#include "light_manager.h"

void LightManager::addLight(std::unique_ptr<Light>&& light) {
    this->lights.push_back(std::move(light));

}

void LightManager::passUniforms(Shader *shader) const {
    shader->passUniform1i("num_lights", this->lights.size());
    for (int i = 0; i < this->lights.size(); i++) {
        std::string prefix = "lights[" + std::to_string(i) + "]";
        this->lights[i]->setUniforms(shader, prefix);
    }
}
