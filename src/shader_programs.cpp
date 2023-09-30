//
// Created by wortelus on 29.9.23.
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

#include "shader_programs.h"

const char* default_vertex_shader =
        "#version 330\n"
        "layout(location=0) in vec3 vp;"
        "void main () {"
        "     gl_Position = vec4 (vp, 1.0);"
        "}";



const char* default_fragment_shader =
        "#version 330\n"
        "out vec4 frag_colour;"
        "void main () {"
        "     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
        "}";


void ShaderPrograms::LoadStaticShaders() {
//    shaders["default_vertex_shader"] = std::make_unique<Shader>(ShaderType::VertexShader, default_vertex_shader);
//    shaders["default_fragment_shader"] = std::make_unique<Shader>(ShaderType::FragmentShader, default_fragment_shader);

    shaders["default"] = std::make_unique<Shader>(ShaderCode{ShaderType::VertexShader, default_vertex_shader},
                                                  ShaderCode{ShaderType::FragmentShader, default_fragment_shader});
}

void ShaderPrograms::LoadShader(const std::string &name) {
    if (shaders.find(name) == shaders.end()) return;
    // TODO: logging system

    shaders[name]->load();
}
