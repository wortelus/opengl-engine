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
#include "../util/const.h"


std::string ShaderLoader::loadShaderFromFile(const std::string &path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void ShaderLoader::loadShaders() {
    for (const auto & entry : std::filesystem::directory_iterator(SHADERS_PATH)) {
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

        shaders[name] = std::make_unique<Shader>(name,
                                                 ShaderCode{ShaderType::VertexShader,
                                                            vertex_shader.c_str()},
                                                 ShaderCode{ShaderType::FragmentShader,
                                                            fragment_shader.c_str()
                                                 });

        printf("Successfully loaded shader %s\n", name.c_str());
    }
}

Shader* ShaderLoader::loadShader(const std::string &name) {
    if (shaders.find(name) == shaders.end()) return nullptr; // <<< TODO: log, shouldn't happen

    if (active_shader != nullptr) shaders[*active_shader]->unload();
    shaders[name]->load();
    active_shader = shaders[name].get()->getName();
    return shaders[name].get();
}

void ShaderLoader::passModelMatrix(const glm::mat4& model) {
    if (active_shader == nullptr) return; // <<< TODO: log, shouldn't happen

    shaders[*active_shader]->passModelMatrix(model);
}

bool ShaderLoader::unloadShader() {
    if (active_shader == nullptr) return false; // <<< TODO: log, shouldn't happen

    shaders[*active_shader]->unload();
    active_shader = nullptr;
    return true;
}

void ShaderLoader::passViewMatrix(const glm::mat4 &view) {
    if (active_shader == nullptr) return; // <<< TODO: log, shouldn't happen
    shaders[*active_shader]->passViewMatrix(view);
}

void ShaderLoader::passProjectionMatrix(const glm::mat4 &projection) {
    if (active_shader == nullptr) return; // <<< TODO: log, shouldn't happen
    shaders[*active_shader]->passProjectionMatrix(projection);
}

void ShaderLoader::passNormalMatrix(const glm::mat3 &normal) {
    if (active_shader == nullptr) return; // <<< TODO: log, shouldn't happen
    shaders[*active_shader]->passNormalMatrix(normal);
}

void ShaderLoader::passCameraPosition(const glm::vec3 &camera_pos) {
    if (active_shader == nullptr) return; // <<< TODO: log, shouldn't happen
    shaders[*active_shader]->passCameraPosition(camera_pos);
}