//
// Created by wortelus on 29.9.23.
//

#ifndef ZPG_SHADER_PROGRAMS_H
#define ZPG_SHADER_PROGRAMS_H

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

#include <unordered_map>
#include <string>
#include <memory>
#include "shader.h"


class ShaderPrograms {
private:
    std::unique_ptr<GLuint> shaderProgram;
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
public:
    void LoadStaticShaders();
    void LoadShader(const std::string &name);
//    void UnloadShader(const std::string &name);

    //[[nodiscard]] Shader* GetShader(const std::string& name) const;
};


#endif //ZPG_SHADER_PROGRAMS_H
