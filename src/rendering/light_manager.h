// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  22/10/2023

#ifndef ZPG_LIGHT_MANAGER_H
#define ZPG_LIGHT_MANAGER_H


#include <vector>
#include <memory>
#include "light/light.h"

class LightManager {
private:
    std::vector<std::unique_ptr<Light>> lights;
public:
    LightManager() = default;
    ~LightManager() = default;

    void addLight(std::unique_ptr<Light>&& light);
    void passUniforms(Shader* shader) const;
};


#endif //ZPG_LIGHT_MANAGER_H
