//
// Created by wortelus on 30.9.23.
//

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

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

Shader::Shader(ShaderCode vertex_shader_code, ShaderCode fragment_shader_code) {
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

void Shader::attachShader(ShaderCode shader_code) {
    if (shader_code.type == ShaderType::VertexShader) {
        if (vertex_shader != 0) {
            // TODO: notify about overwriting shader
            glDeleteShader(vertex_shader);
        }
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &shader_code.source, NULL);
        glCompileShader(vertex_shader);
    } else if (shader_code.type == ShaderType::FragmentShader) {
        if (fragment_shader != 0) {
            // TODO: notify about overwriting shader
            glDeleteShader(fragment_shader);
        }
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &shader_code.source, NULL);
        glCompileShader(fragment_shader);
    }
}
