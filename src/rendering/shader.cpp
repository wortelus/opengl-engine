// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/9/2023

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

#include <utility>

//Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "shader.h"


void Shader::load() {
    if (active) return;
    glUseProgram(shader_program);
    active = true;
}

void Shader::unload() {
    //TODO: unload
    if (!active) return;
    glUseProgram(0);
    active = false;
}

Shader::Shader(const SHADER_ALIAS_DATATYPE shader_alias,
               std::string  name,
               const ShaderCode& vertex_shader_code,
               const ShaderCode& fragment_shader_code) :
               alias(shader_alias),
               name(std::move(name)) {
    attachShader(vertex_shader_code);
    attachShader(fragment_shader_code);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, fragment_shader);
    glAttachShader(shader_program, vertex_shader);
    glLinkProgram(shader_program);
}


Shader::~Shader() {
    glDeleteProgram(shader_program);
}

void Shader::attachShader(const ShaderCode& shader_code) {
    if (shader_code.type == ShaderType::VertexShader) {
        if (vertex_shader != 0) {
            // TODO: notify about overwriting shader
            glDeleteShader(vertex_shader);
        }
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &shader_code.source, nullptr);
        glCompileShader(vertex_shader);
    } else if (shader_code.type == ShaderType::FragmentShader) {
        if (fragment_shader != 0) {
            // TODO: notify about overwriting shader
            glDeleteShader(fragment_shader);
        }
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &shader_code.source, nullptr);
        glCompileShader(fragment_shader);
    }
}

void Shader::update(const EventArgs &event_args) {

}

void Shader::passModelMatrix(const glm::mat4 &model) const {
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "model_matrix"),
                       1, GL_FALSE, glm::value_ptr(model));
}

void Shader::passViewMatrix(const glm::mat4 &view) const {
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "view_matrix"),
                       1, GL_FALSE, glm::value_ptr(view));
}

void Shader::passProjectionMatrix(const glm::mat4 &projection) const {
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection_matrix"),
                       1, GL_FALSE, glm::value_ptr(projection));
}

void Shader::passNormalMatrix(const glm::mat3 &normal) const {
    glUniformMatrix3fv(glGetUniformLocation(shader_program, "normal_matrix"),
                       1, GL_FALSE, glm::value_ptr(normal));
}

void Shader::passCameraPosition(const glm::vec3 &camera_pos) const {
    glUniform3fv(glGetUniformLocation(shader_program, "camera_position"),
                 1, glm::value_ptr(camera_pos));
}

void Shader::passUniform1i(const std::string &uniform_name, int value) const {
    glUniform1i(glGetUniformLocation(shader_program, uniform_name.c_str()), value);
}

void Shader::passUniform1f(const std::string &uniform_name, float value) const {
    glUniform1f(glGetUniformLocation(shader_program, uniform_name.c_str()), value);
}

void Shader::passUniform3fv(const std::string &uniform_name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(shader_program, uniform_name.c_str()),
                 1, glm::value_ptr(value));
}

void Shader::passUniform4fv(const std::string &uniform_name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(shader_program, uniform_name.c_str()),
                 1, glm::value_ptr(value));
}

void Shader::passUniformMatrix3fv(const std::string &uniform_name, const glm::mat3 &value) const {
    glUniformMatrix3fv(glGetUniformLocation(shader_program, uniform_name.c_str()),
                       1, GL_FALSE, glm::value_ptr(value));
}

void Shader::passUniformMatrix4fv(const std::string &uniform_name, const glm::mat4 &value) const {
    glUniformMatrix4fv(glGetUniformLocation(shader_program, uniform_name.c_str()),
                       1, GL_FALSE, glm::value_ptr(value));
}