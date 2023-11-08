// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  16/10/2023

#ifndef ZPG_POINT_LIGHT_H
#define ZPG_POINT_LIGHT_H

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <algorithm>

//Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr
#include "light.h"

class PointLight : public Light {
private:
    glm::vec3 position;
    Attenuation attenuation;
public:
    PointLight(const glm::vec3& position,
               const glm::vec3& color,
               const float& intensity,
               const float& constant, const float& linear, const float& quadratic)
            : Light(color, intensity), position(position), attenuation({constant, linear, quadratic}) {}

    [[nodiscard]] const glm::vec3& getPosition() const { return position; }
    [[nodiscard]] const Attenuation& getAttenuation() const { return attenuation; }

    static constexpr std::array<const char*, 6> getParameterNames() {
        return std::array<const char*, 6>{
                "position",
                "color",
                "intensity",
                "constant",
                "linear",
                "quadratic"
        };
    }

    [[nodiscard]] std::array<LightProperty, 6> getParameters() const;
};

#endif //ZPG_POINT_LIGHT_H
