// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  22/10/2023

#include "light_manager.h"
#include "light/point_light.h"
#include "light/directional_light.h"
#include "light/spotlight.h"

LightManager::LightManager() {
    this->lights = std::make_shared<std::vector<std::shared_ptr<Light>>>();
}

LIGHT_ID LightManager::addLight(const Light& light) {
    const auto* point_light = dynamic_cast<const PointLight*>(&light);
    if (point_light != nullptr) {
        this->lights->push_back(std::make_shared<PointLight>(*point_light));
        return static_cast<LIGHT_ID>(this->lights->size() - 1);
    }
    const auto* directional_light = dynamic_cast<const DirectionalLight*>(&light);
    if (directional_light != nullptr) {
        this->lights->push_back(std::make_shared<DirectionalLight>(*directional_light));
        return static_cast<LIGHT_ID>(this->lights->size() - 1);
    }
    const auto* spot_light = dynamic_cast<const Spotlight*>(&light);
    if (spot_light != nullptr) {
        this->lights->push_back(std::make_shared<Spotlight>(*spot_light));
        return static_cast<LIGHT_ID>(this->lights->size() - 1);
    }
}

LIGHT_ID LightManager::addLight(const std::shared_ptr<Light>& light) {
    this->lights->push_back(light);
    return static_cast<LIGHT_ID>(this->lights->size() - 1);
}

void LightManager::notifyShaders() {
    EventPayload<std::shared_ptr<std::vector<std::shared_ptr<Light>>>> payload{this->lights, EventType::U_LIGHTS};
    notify(payload);
}
