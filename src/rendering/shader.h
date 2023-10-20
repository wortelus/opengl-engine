// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/9/2023

#ifndef ZPG_SHADER_H
#define ZPG_SHADER_H

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
#include <memory>

#include "../util/observer.h"

enum class ShaderType {
    VertexShader = GL_VERTEX_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER,
};

struct ShaderCode {
    ShaderType type;
    const char* source;
};

class Shader : public IObserver {
private:
    std::shared_ptr<std::string> name;
    GLuint shader_program = 0;

    GLuint vertex_shader = 0;
    GLuint fragment_shader = 0;

    bool active = false;

    void attachShader(const ShaderCode& shader_code);
public:
    Shader(const std::string &name, const ShaderCode& vertex_shader_code, const ShaderCode& fragment_shader_code);
    ~Shader();

    void load();
    void unload();

    [[nodiscard]] bool isLoaded() const { return active; }
    [[nodiscard]] std::shared_ptr<std::string> getName() const { return name; }

    void passModelMatrix(const glm::mat4 &model) const;
    void passViewMatrix(const glm::mat4 &view) const;
    void passProjectionMatrix(const glm::mat4 &projection) const;
    void passNormalMatrix(const glm::mat3 &normal) const;

    void update(const EventArgs& event_args) override;
};


#endif //ZPG_SHADER_H
