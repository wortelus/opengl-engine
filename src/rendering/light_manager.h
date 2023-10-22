//
// Created by wortelus on 22.10.23.
//

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
