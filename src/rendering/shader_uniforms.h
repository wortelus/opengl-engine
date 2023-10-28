// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  28/10/2023

#ifndef ZPG_SHADER_UNIFORMS_H
#define ZPG_SHADER_UNIFORMS_H

#include <GL/glew.h>
#include <memory>
#include "glm/ext/matrix_float4x4.hpp"

#include "light/light.h"
#include "../models/material.h"
#include "../util/event_args.h"

template<typename T>
struct ShaderUniform {
    T value;
    bool is_dirty = false;
    GLint location = -1;

    ShaderUniform() = default;
    explicit ShaderUniform(GLint loc) : location(loc) {}
};

struct ShaderUniforms {
    ShaderUniform<std::shared_ptr<glm::mat4>> model;
    ShaderUniform<glm::mat4> view;
    ShaderUniform<glm::mat4> projection;
    ShaderUniform<std::shared_ptr<glm::mat3>> normal;
    ShaderUniform<glm::vec3> camera_position;

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
