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
#include <algorithm>

#include "shader_loader.h"

const char* default_vertex_shader =
        "#version 330\n"
        "layout(location=0) in vec4 vposition;"
        "layout(location=1) in vec3 vcolor;"
        "uniform mat4 transform;"
        "out vec3 fragmentColor;"
        "void main () {"
        "     gl_Position = transform * vposition;"
        "     fragmentColor = vcolor;"
        "}";



const char* default_fragment_shader =
        "#version 330\n"
        "in vec3 fragmentColor;"
        "out vec4 frag_colour;"
        "void main () {"
        "     frag_colour = vec4 (fragmentColor, 1.0);"
        "}";


void ShaderLoader::LoadStaticShaders() {
    shaders["default"] = std::make_unique<Shader>("default", ShaderCode{ShaderType::VertexShader, default_vertex_shader},
                                                  ShaderCode{ShaderType::FragmentShader, default_fragment_shader});
}

bool ShaderLoader::LoadShader(const std::string &name) {
    if (shaders.find(name) == shaders.end()) return false;
    // TODO: logging system
//    std::for_each(shaders.begin(), shaders.end(), [](auto& shader) {
//        shader.second->unload();
//    });
    if (active_shader != nullptr) shaders[*active_shader]->unload();
    shaders[name]->load();
    active_shader = shaders[name].get()->getName();
    return true;
}

void ShaderLoader::PassTransform(const glm::mat4& model) {
    if (active_shader == nullptr) {
        // TODO: log, shouldn't happen
        return;
    }
    shaders[*active_shader]->PassTransform(model);
}

bool ShaderLoader::UnloadShader() {
    if (active_shader == nullptr) return false;
    shaders[*active_shader]->unload();
    active_shader = nullptr;
    return true;
}
