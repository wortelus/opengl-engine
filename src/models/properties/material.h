// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  22/10/2023

#ifndef ZPG_MATERIAL_H
#define ZPG_MATERIAL_H

#include "glm/vec3.hpp"
#include "../../util/const.h"
#include "texture.h"

enum ILLUMINATION {
    AMBIENT = (1u << 0),
    DIFFUSE = (1u << 1),
    SPECULAR = (1u << 2),
    ALL = AMBIENT | DIFFUSE | SPECULAR
};

struct Material {
    const Texture* texture = nullptr;

    glm::vec3 ambient = AMBIENT_LIGHT;
    glm::vec3 diffuse = glm::vec3(0.0);
    glm::vec3 specular = glm::vec3(0.0);
    float shininess = 0.f;

    ILLUMINATION illuminated = ILLUMINATION::AMBIENT;

    Material() = default;

    explicit Material(const glm::vec3& _ambient)
            : ambient(_ambient) {
        this->illuminated = ILLUMINATION::AMBIENT;
    }

    Material(const glm::vec3& _ambient, const glm::vec3& _diffuse)
            : ambient(_ambient), diffuse(_diffuse) {
        this->illuminated = static_cast<ILLUMINATION>(ILLUMINATION::AMBIENT | ILLUMINATION::DIFFUSE);
    }

    Material(const glm::vec3& _diffuse, const glm::vec3& _specular, float _shininess)
            : diffuse(_diffuse), specular(_specular), shininess(_shininess) {
        this->illuminated = ILLUMINATION::ALL;
    }

    Material(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular, float _shininess)
            : ambient(_ambient), diffuse(_diffuse), specular(_specular), shininess(_shininess) {
        this->illuminated = ILLUMINATION::ALL;
    }
};

#endif //ZPG_MATERIAL_H
