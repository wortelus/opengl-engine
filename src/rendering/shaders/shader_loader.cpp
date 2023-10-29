// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/9/2023

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr
#include <algorithm>
#include <filesystem>
#include <fstream>

#include "shader_loader.h"
#include "../../util/const.h"


std::string ShaderLoader::loadShaderFromFile(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void ShaderLoader::loadShaders() {
    for (const auto& entry: std::filesystem::directory_iterator(SHADERS_PATH)) {
        if (entry.is_directory()) continue;
        std::string path = entry.path().string();
        std::string name = entry.path().stem().string();
        std::string extension = entry.path().extension().string();

        if (extension != ".vert")
            continue;

        std::string fragment_path = path.substr(0, path.size() - 4) + "frag";

        if (!std::filesystem::exists(fragment_path)) {
            printf("Fragment shader for %s not found\n", name.c_str());
            exit(22);
        }

        std::string vertex_shader = loadShaderFromFile(path);
        std::string fragment_shader = loadShaderFromFile(fragment_path);

        auto next_alias = static_cast<SHADER_ALIAS_DATATYPE>(shaders.size());

        shaders.push_back(std::make_unique<Shader>(next_alias, name,
                                                   ShaderCode{ShaderType::VertexShader,
                                                              vertex_shader.c_str()},
                                                   ShaderCode{ShaderType::FragmentShader,
                                                              fragment_shader.c_str()
                                                   }));

        printf("Successfully is_dirty shader %s(%d)\n", name.c_str(), next_alias);
    }
}

Shader* ShaderLoader::loadShader(const SHADER_ALIAS_DATATYPE& alias) {
    // no loading needed, save gl instruction by omitting glUseProgram
    if (this->active_shader == alias) return shaders[alias].get();

    if (this->active_shader != SHADER_UNLOADED) shaders[this->active_shader]->unload();
    shaders[alias]->load();
    active_shader = alias;
    return shaders[alias].get();
}

bool ShaderLoader::unloadShader() {
    if (active_shader == SHADER_UNLOADED) return false; // <<< TODO: log, shouldn't happen

    shaders[active_shader]->unload();
    active_shader = SHADER_UNLOADED;
    return true;
}

SHADER_ALIAS_DATATYPE ShaderLoader::getShaderAlias(const std::string& name) {
    for (const auto& shader: shaders) {
        if (shader->getName() == name) return shader->getAlias();
    }
    return SHADER_UNLOADED;
}
