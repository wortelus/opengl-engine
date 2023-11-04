// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  22/10/2023

#ifndef ZPG_LIGHT_MANAGER_H
#define ZPG_LIGHT_MANAGER_H


#include <vector>
#include <memory>
#include "light/light.h"
#include "../util/observer.h"
#include "../util/event_args.h"
#include "../util/const_lights.h"

class LightManager : public ISubject {
private:
    std::shared_ptr<std::vector<std::shared_ptr<Light>>> lights;
public:
    LightManager();
    ~LightManager() = default;

    LIGHT_ID addLight(const Light& light);
    LIGHT_ID addLight(const std::shared_ptr<Light>& light);

    [[nodiscard]] std::shared_ptr<Light> getLight(LIGHT_ID id) const { return this->lights->at(id); }

    void notifyShaders();
};


#endif //ZPG_LIGHT_MANAGER_H
