// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/9/2023

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

#include <utility>

//Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "shader.h"


void Shader::load() {
    if (active) return;
    glUseProgram(shader_program);
    active = true;
}

void Shader::unload() {
    //TODO: unload
    if (!active) return;
    glUseProgram(0);
    active = false;
}

Shader::Shader(const SHADER_ALIAS_DATATYPE shader_alias,
               std::string name,
               const ShaderCode& vertex_shader_code,
               const ShaderCode& fragment_shader_code) :
        alias(shader_alias),
        name(std::move(name)) {
    attachShader(vertex_shader_code);
    attachShader(fragment_shader_code);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, fragment_shader);
    glAttachShader(shader_program, vertex_shader);
    glLinkProgram(shader_program);
}


Shader::~Shader() {
    glDeleteProgram(shader_program);
}

void Shader::attachShader(const ShaderCode& shader_code) {
    if (shader_code.type == ShaderType::VertexShader) {
        if (vertex_shader != 0) {
            // TODO: notify about overwriting shader
            glDeleteShader(vertex_shader);
        }
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &shader_code.source, nullptr);
        glCompileShader(vertex_shader);
    } else if (shader_code.type == ShaderType::FragmentShader) {
        if (fragment_shader != 0) {
            // TODO: notify about overwriting shader
            glDeleteShader(fragment_shader);
        }
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &shader_code.source, nullptr);
        glCompileShader(fragment_shader);
    }
}

void Shader::update(const EventArgs& event_args) {
    if (event_args.type == EventType::U_LIGHTS) {
        updateLights(event_args);
        return;
    }
    if (event_args.type == EventType::U_MATERIAL) {
        updateMaterial(event_args);
        return;
    }

    if (event_args.type < EventType::U_1I) {
        uniforms.passEvent(event_args);
        return;
    }

    switch (event_args.type) {
        case EventType::U_1I: {
            const auto* uniform = static_cast<const EventPayload<int>*>(&event_args);
            passUniform1i(uniform->name, uniform->getPayload());
            break;
        }
        case EventType::U_1F: {
            const auto* uniform = static_cast<const EventPayload<float>*>(&event_args);
            passUniform1f(uniform->name, uniform->getPayload());
            break;
        }
        case EventType::U_3FV: {
            const auto* uniform = static_cast<const EventPayload<glm::vec3>*>(&event_args);
            passUniform3fv(uniform->name, uniform->getPayload());
            break;
        }
        case EventType::U_4FV: {
            const auto* uniform = static_cast<const EventPayload<glm::vec4>*>(&event_args);
            passUniform4fv(uniform->name, uniform->getPayload());
            break;
        }
        case EventType::U_MAT_3FV: {
            const auto* uniform = static_cast<const EventPayload<glm::mat3>*>(&event_args);
            passUniformMatrix3fv(uniform->name, uniform->getPayload());
            break;
        }
        case EventType::U_MAT_4FV: {
            const auto* uniform = static_cast<const EventPayload<glm::mat4>*>(&event_args);
            passUniformMatrix4fv(uniform->name, uniform->getPayload());
            break;
        }
        default:
            break;
    }
}

void Shader::passUniform1i(const std::string& uniform_name, int value) const {
    glUniform1i(glGetUniformLocation(shader_program, uniform_name.c_str()), value);
}

void Shader::passUniform1f(const std::string& uniform_name, float value) const {
    glUniform1f(glGetUniformLocation(shader_program, uniform_name.c_str()), value);
}

void Shader::passUniform3fv(const std::string& uniform_name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(shader_program, uniform_name.c_str()),
                 1, glm::value_ptr(value));
}

void Shader::passUniform4fv(const std::string& uniform_name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(shader_program, uniform_name.c_str()),
                 1, glm::value_ptr(value));
}

void Shader::passUniformMatrix3fv(const std::string& uniform_name, const glm::mat3& value) const {
    glUniformMatrix3fv(glGetUniformLocation(shader_program, uniform_name.c_str()),
                       1, GL_FALSE, glm::value_ptr(value));
}

void Shader::passUniformMatrix4fv(const std::string& uniform_name, const glm::mat4& value) const {
    glUniformMatrix4fv(glGetUniformLocation(shader_program, uniform_name.c_str()),
                       1, GL_FALSE, glm::value_ptr(value));
}

void Shader::lazyPassUniforms() {
    uniforms.updateUniforms();
    if (lights_collection.is_dirty) {
        passLightsUniforms();
        lights_collection.is_dirty = false;
    }
    if (material.is_dirty) {
        passMaterialUniforms();
        material.is_dirty = false;
    }
}

void Shader::initUniforms() {
    uniforms.model.location = glGetUniformLocation(shader_program, "model_matrix");
    uniforms.view.location = glGetUniformLocation(shader_program, "view_matrix");
    uniforms.projection.location = glGetUniformLocation(shader_program, "projection_matrix");
    uniforms.normal.location = glGetUniformLocation(shader_program, "normal_matrix");
    uniforms.camera_position.location = glGetUniformLocation(shader_program, "camera_position");
}

void Shader::updateLights(const EventArgs& event_args) {
    const auto* lights = static_cast<const EventPayload<std::shared_ptr<std::vector<std::shared_ptr<Light>>>>*>(&event_args);
    this->lights_collection.value = std::move(lights->getPayload());
    this->lights_collection.is_dirty = true;
}

void Shader::passLightsUniforms() {
    int num_lights = this->lights_collection.value->size();

    passUniform1i("num_lights", num_lights);
    for (int i = 0; i < num_lights; i++) {
        std::string prefix = "lights[" + std::to_string(i) + "]";
        passLight((*this->lights_collection.value)[i], prefix);
    }
}

void Shader::passLight(const std::shared_ptr<Light>& light, const std::string& prefix) const {
    auto pos = light->getPosition();
    auto color = light->getColor();
    auto intensity = light->getIntensity();
    auto attenuation = light->getAttenuation();
    passUniform3fv(prefix + ".position", pos);
    passUniform3fv(prefix + ".color", color);
    passUniform1f(prefix + ".intensity", intensity);
    passUniform1f(prefix + ".constant", attenuation.constant);
    passUniform1f(prefix + ".linear", attenuation.linear);
    passUniform1f(prefix + ".quadratic", attenuation.quadratic);
}

void Shader::updateMaterial(const EventArgs& event_args) {
    auto* material_payload = static_cast<const EventPayload<Material>*>(&event_args);
    this->material.value = material_payload->getPayload();
    this->material.is_dirty = true;
}

void Shader::passMaterialUniforms() {
    // TODO: remove object color?
    passUniform3fv("object_color", material.value.object_color);

    passUniform3fv("material.ambient", material.value.ambient);
    if (true)
        passUniform3fv("material.diffuse", material.value.diffuse);
    if (true) {
        passUniform3fv("material.specular", material.value.specular);
        passUniform1f("material.shininess", material.value.shininess);
    }
    material.is_dirty = false;
}
