// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  3/11/2023

#ifndef ZPG_LIGHT_H
#define ZPG_LIGHT_H

#include <array>
#include <vector>
#include <string>
#include <tuple>
#include <variant>
#include <GL/glew.h>
#include "glm/vec3.hpp"
#include "glm/ext/matrix_float3x3.hpp"

using LIGHT_ID = int;

using LightProperty =
        std::variant<
                const glm::mat3*,
                const glm::mat4*,
                const glm::vec3*,
                const GLint*,
                const GLfloat*
        >;

struct Attenuation {
    float constant;
    float linear;
    float quadratic;
};

class Light {
private:
    LIGHT_ID managed_id = -1;
protected:
    glm::vec3 color;
    float intensity;
public:
    Light(const glm::vec3& color, const float& intensity) : color(color), intensity(intensity) {}
    virtual ~Light() = default;

    void setManagedId(LIGHT_ID id) { this->managed_id = id; }
    [[nodiscard]] LIGHT_ID getManagedId() const;

    [[nodiscard]] const glm::vec3& getColor() const { return color; }
    [[nodiscard]] float getIntensity() const { return intensity; }

    [[nodiscard]] virtual std::vector<std::tuple<std::string, LightProperty>> getParameters() const = 0;
};


#endif //ZPG_LIGHT_H
