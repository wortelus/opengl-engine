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

#include "../../util/observer.h"
#include "../../util/const.h"

#include "uniforms/shader_uniforms.h"
#include "../light/light.h"
#include "uniforms/dynamic_uniforms.h"

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
    SHADER_ALIAS_DATATYPE alias;
    std::string name;

    bool active = false;

    GLuint shader_program = 0;
    GLuint vertex_shader = 0;
    GLuint fragment_shader = 0;

    ShaderUniforms uniforms;

    DynamicUniforms dynamic_uniforms;
    ShaderUniform<Material> material;
private:
    void attachShader(const ShaderCode& shader_code);

    void initLightUniforms();
    template <std::size_t SIZE>
    void initLightUniform(std::array<int, SIZE>& uniform_locations, SHADER_UNIFORM_LOCATION& num_uniform_location,
                                  const char* collection_name, const char* count_name,
                                  int max_light_count, int light_param_count);

    void updateMaterial(const EventArgs& event_args);
    void passMaterialUniforms();
public:
    Shader(const SHADER_ALIAS_DATATYPE shader_alias, std::string name,
           const ShaderCode& vertex_shader_code, const ShaderCode& fragment_shader_code);
    ~Shader() override;

    void initUniforms();
    void lazyPassUniforms();

    void load();
    void unload();

    [[nodiscard]] SHADER_ALIAS_DATATYPE getAlias() const { return alias; }

    [[nodiscard]] bool isLoaded() const { return active; }

    [[nodiscard]] std::string getName() const { return name; }

    void update(const EventArgs& event_args) override;

    void passUniform1i(const std::string& uniform_name, int value) const;
    void passUniform1f(const std::string& uniform_name, float value) const;
    void passUniform3fv(const std::string& uniform_name, const glm::vec3& value) const;
    void passUniform4fv(const std::string& uniform_name, const glm::vec4& value) const;
    void passUniformMatrix3fv(const std::string& uniform_name, const glm::mat3& value) const;
    void passUniformMatrix4fv(const std::string& uniform_name, const glm::mat4& value) const;
};


#endif //ZPG_SHADER_H
