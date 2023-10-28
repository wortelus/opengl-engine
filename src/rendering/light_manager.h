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

class LightManager : public ISubject {
private:
    std::shared_ptr<std::vector<std::shared_ptr<Light>>> lights;
public:
    LightManager();
    ~LightManager() = default;

    void addLight(const Light& light);
    void addLight(const std::shared_ptr<Light>& light);

    void notifyShaders();
};


#endif //ZPG_LIGHT_MANAGER_H
