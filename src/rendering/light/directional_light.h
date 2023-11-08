// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  3/11/2023

#ifndef ZPG_DIRECTIONAL_LIGHT_H
#define ZPG_DIRECTIONAL_LIGHT_H


#include <tuple>
#include "glm/vec3.hpp"
#include "light.h"

class DirectionalLight : public Light {
private:
    glm::vec3 direction;
public:
    DirectionalLight(const glm::vec3& direction,
                     const glm::vec3& color,
                     const float& intensity)
            : Light(color, intensity), direction(direction) {}

    [[nodiscard]] const glm::vec3& getDirection() const { return direction; }

    static constexpr std::array<const char*, 3> getParameterNames() {
        return std::array<const char*, 3>{
                "direction",
                "color",
                "intensity"
        };
    }

    [[nodiscard]] std::array<LightProperty, 3> getParameters() const;
};


#endif //ZPG_DIRECTIONAL_LIGHT_H
