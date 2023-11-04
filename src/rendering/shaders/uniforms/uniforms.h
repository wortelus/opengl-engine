//
// Created by wortelus on 3.11.23.
//

#ifndef ZPG_UNIFORMS_H
#define ZPG_UNIFORMS_H


#include <GL/glew.h>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/ext/matrix_float3x3.hpp"
#include "glm/ext/matrix_float4x4.hpp"

template<typename T>
struct ShaderUniform {
    T value;
    bool is_dirty = false;
    GLint location = -1;

    ShaderUniform() = default;
};

class Uniforms {
public:
    static void passUniform1i(GLint location, GLint value);
    static void passUniform1f(GLint location, GLfloat value);
    static void passUniform3fv(GLint location, const glm::vec3& value);
    static void passUniform4fv(GLint location, const glm::vec4& value);
    static void passUniformMatrix3fv(GLint location, const glm::mat3& value);
    static void passUniformMatrix4fv(GLint location, const glm::mat4& value);
};


#endif //ZPG_UNIFORMS_H
