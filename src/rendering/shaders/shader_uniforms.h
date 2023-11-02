// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  28/10/2023

#ifndef ZPG_SHADER_UNIFORMS_H
#define ZPG_SHADER_UNIFORMS_H

#include <GL/glew.h>
#include <memory>
#include "glm/ext/matrix_float4x4.hpp"

#include "../light/light.h"
#include "../../models/material.h"
#include "../../util/event_args.h"

template<typename T>
struct ShaderUniform {
    T value;
    bool is_dirty = false;
    GLint location = -1;

    ShaderUniform() = default;
};

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
    ShaderUniforms() = default;

    void passEvent(const EventArgs& event_args);
    void updateUniforms();
private:
    static void passUniform1i(GLint location, GLint value);
    static void passUniform1f(GLint location, GLfloat value);
    static void passUniform3fv(GLint location, const glm::vec3& value);
    static void passUniform4fv(GLint location, const glm::vec4& value);
    static void passUniformMatrix3fv(GLint location, const glm::mat3& value);
    static void passUniformMatrix4fv(GLint location, const glm::mat4& value);
};


#endif //ZPG_SHADER_UNIFORMS_H
