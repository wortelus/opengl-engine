//
// Created by wortelus on 3.11.23.
//

#include "uniforms.h"
#include "glm/gtc/type_ptr.hpp"


void Uniforms::passUniform1i(GLint location, GLint value) {
    glUniform1i(location, value);
}

void Uniforms::passUniform1f(GLint location, GLfloat value) {
    glUniform1f(location, value);
}

void Uniforms::passUniform3fv(GLint location, const glm::vec3& value) {
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Uniforms::passUniform4fv(GLint location, const glm::vec4& value) {
    glUniform4fv(location, 1, glm::value_ptr(value));

}

void Uniforms::passUniformMatrix3fv(GLint location, const glm::mat3& value) {
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Uniforms::passUniformMatrix4fv(GLint location, const glm::mat4& value) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
