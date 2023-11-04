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

    static constexpr std::array<const char*, 3> getParameterNames();
    [[nodiscard]] std::vector<std::tuple<std::string, LightProperty>> getParameters() const final;
};


#endif //ZPG_DIRECTIONAL_LIGHT_H
