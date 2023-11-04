// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  3/11/2023

#ifndef ZPG_SPOTLIGHT_H
#define ZPG_SPOTLIGHT_H


#include "glm/vec3.hpp"
#include "point_light.h"

class Spotlight : public Light {
private:
    glm::vec3 position;
    glm::vec3 direction;
    Attenuation attenuation;

    float cutoff;
    float outer_cutoff;
public:
    Spotlight(const glm::vec3& position,
              const glm::vec3& direction,
              const glm::vec3& color,
              const float& intensity,
              const float& constant,
              const float& linear,
              const float& quadratic,
              const float& cutoff,
              const float& outerCutoff)
            : Light(color, intensity), position(position), direction(direction),
              attenuation{constant, linear, quadratic},
              cutoff(cutoff), outer_cutoff(outerCutoff) {}

    [[nodiscard]] const glm::vec3& getPosition() const { return position; }
    [[nodiscard]] const glm::vec3& getDirection() const { return direction; }
    [[nodiscard]] const Attenuation& getAttenuation() const { return attenuation; }
    [[nodiscard]] float getCutoff() const { return cutoff; }
    [[nodiscard]] float getOuterCutoff() const { return outer_cutoff; }


    static constexpr std::array<const char*, 9> getParameterNames() {
        return std::array<const char*, 9>{
                "position",
                "direction",
                "color",
                "intensity",
                "constant",
                "linear",
                "quadratic",
                "cutoff",
                "outer_cutoff"
        };
    }

    [[nodiscard]] std::vector<std::tuple<std::string, LightProperty>> getParameters() const final;
};


#endif //ZPG_SPOTLIGHT_H
