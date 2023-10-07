// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/9/2023

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


const char* normale_vertex_shader =
        "#version 330\n"
        "layout(location=0) in vec3 vposition;"
        "layout(location=1) in vec3 vnormal;"
        "uniform mat4 transform;"
        "out vec4 frag_color;"
        "out vec3 frag_normal;"
        "void main () {"
        "     gl_Position = transform * vec4(vposition, 1.0);"
        "     frag_color = vec4 (1.0, 0.5, 0, 1.0);"
        "     frag_normal = vnormal;"
        "}";



const char* normale_fragment_shader =
        "#version 330\n"
        "in vec4 frag_color;"
        "out vec4 frag_color_out;"
        "void main () {"
        "     frag_color_out = frag_color;"
        "}";


void ShaderLoader::loadStaticShaders() {
    shaders["default"] = std::make_unique<Shader>("default", ShaderCode{ShaderType::VertexShader, default_vertex_shader},
                                                  ShaderCode{ShaderType::FragmentShader, default_fragment_shader});
    shaders["normale"] = std::make_unique<Shader>("normale", ShaderCode{ShaderType::VertexShader, normale_vertex_shader},
                                                  ShaderCode{ShaderType::FragmentShader, normale_fragment_shader});
}

bool ShaderLoader::loadShader(const std::string &name) {
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

void ShaderLoader::passTransform(const glm::mat4& model) {
    if (active_shader == nullptr) {
        // TODO: log, shouldn't happen
        return;
    }
    shaders[*active_shader]->passTransform(model);
}

bool ShaderLoader::unloadShader() {
    if (active_shader == nullptr) return false;
    shaders[*active_shader]->unload();
    active_shader = nullptr;
    return true;
}
