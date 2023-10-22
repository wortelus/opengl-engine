// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  16/10/2023

#ifndef ZPG_LIGHT_H
#define ZPG_LIGHT_H

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
#include "../shader.h"

struct Attenuation {
    float constant;
    float linear;
    float quadratic;
};

class Light {
private:
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
public:
    Light(const glm::vec3& position,
          const glm::vec3& color,
          const float& intensity) :
          position(position), color(color), intensity(intensity) { };
    virtual void setUniforms(Shader *shader, const std::string& prefix) const;
};

class PhongLight : public Light {
private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Attenuation attenuation;
public:
    PhongLight(
            const glm::vec3& position,
            const glm::vec3& color,
            const float& intensity,
            const float& constant,
            const float& linear,
            const float& quadratic) : Light(position, color, intensity),
            attenuation({constant, linear, quadratic}) { };
    void setUniforms(Shader* shader, const std::string& prefix) const override;
};


#endif //ZPG_LIGHT_H
