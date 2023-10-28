// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  22/10/2023

#include "light_manager.h"

LightManager::LightManager() {
    this->lights = std::make_shared<std::vector<std::shared_ptr<Light>>>();
}

void LightManager::addLight(const Light& light) {
    this->lights->push_back(std::make_shared<Light>(light));
}

void LightManager::addLight(const std::shared_ptr<Light>& light) {
    this->lights->push_back(light);
}

void LightManager::notifyShaders() {
    EventPayload<std::shared_ptr<std::vector<std::shared_ptr<Light>>>> payload {this->lights, EventType::U_LIGHTS};
    notify(payload);
}
