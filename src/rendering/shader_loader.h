// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/9/2023

#ifndef ZPG_SHADER_LOADER_H
#define ZPG_SHADER_LOADER_H

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

#include <unordered_map>
#include <string>
#include <memory>
#include "shader.h"


class ShaderLoader {
private:
    std::shared_ptr<std::string> active_shader;
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
public:
    void loadStaticShaders();
    bool loadShader(const std::string &name);
    bool unloadShader();
    void passModelMatrix(const glm::mat4 &model);
    void passViewMatrix(const glm::mat4 &view);
    void passProjectionMatrix(const glm::mat4 &projection);
//    void unloadShader(const std::string &name);

    //[[nodiscard]] Shader* GetShader(const std::string& name) const;
};


#endif //ZPG_SHADER_LOADER_H
