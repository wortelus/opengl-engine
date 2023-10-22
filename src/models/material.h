// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  22/10/2023

#ifndef ZPG_MATERIAL_H
#define ZPG_MATERIAL_H

#include "glm/vec3.hpp"

struct Material {
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    Material(const glm::vec3& _diffuse, const glm::vec3& _specular, float _shininess)
    : diffuse(_diffuse), specular(_specular), shininess(_shininess) {}
};

#endif //ZPG_MATERIAL_H
