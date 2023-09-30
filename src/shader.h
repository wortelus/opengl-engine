//
// Created by wortelus on 30.9.23.
//

#ifndef ZPG_SHADER_H
#define ZPG_SHADER_H

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

#include "observer.h"

enum class ShaderType {
    VertexShader = GL_VERTEX_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER,
};

struct ShaderCode {
    ShaderType type;
    const char* source;
};

class Shader {
private:
    std::string name;
    GLuint shader_program = 0;

    GLuint vertex_shader = 0;
    GLuint fragment_shader = 0;

    bool active = false;

    void attachShader(ShaderCode shader_code);
public:
    Shader(ShaderCode vertex_shader, ShaderCode fragment_shader);
    ~Shader();

    void load();
    void unload();

//    [[nodiscard]] GLuint getShader() const { return shader_program; }
    [[nodiscard]] bool isLoaded() const { return active; }
};


#endif //ZPG_SHADER_H
