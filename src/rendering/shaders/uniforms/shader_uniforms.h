// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  28/10/2023

#ifndef ZPG_SHADER_UNIFORMS_H
#define ZPG_SHADER_UNIFORMS_H

#include <GL/glew.h>
#include <memory>
#include "glm/ext/matrix_float4x4.hpp"

#include "../../light/light.h"
#include "../../../models/properties/material.h"
#include "../../../util/event_args.h"
#include "uniforms.h"

struct ShaderUniforms {
public:
    //
    // IMPORTANT NOTE: These transformations use raw pointers to matrices, because they are not owned by this class and for the sake of performance.
    // To ensure stable scene, you have to make sure that the matrices are not deleted (or REALLOCATED!) while the scene is being rendered.
    // Please, for the sake of your sanity, delete your objects out of the render loop if necessary.
    //
    ShaderUniform<const glm::mat4*> model;
    ShaderUniform<const glm::mat4*> view;
    ShaderUniform<const glm::mat4*> projection;
    ShaderUniform<const glm::mat3*> normal;
    ShaderUniform<const glm::vec3*> camera_position;
    ShaderUniform<TEXTURE_UNIT> texture_unit{.value = 0}; // default texture unit is 0
    ShaderUniforms() = default;

    void passEvent(const EventArgs& event_args);
    void lazyPassUniforms();
};


#endif //ZPG_SHADER_UNIFORMS_H
