// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/9/2023

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

#include <utility>
#include <stdexcept>

//Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "shader.h"
#include "../light/point_light.h"


void Shader::load() {
    if (active) return;
    glUseProgram(shader_program);
    active = true;
}

void Shader::unload() {
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
            throw std::runtime_error("Vertex shader already attached");
            glDeleteShader(vertex_shader);
        }
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &shader_code.source, nullptr);
        glCompileShader(vertex_shader);
    } else if (shader_code.type == ShaderType::FragmentShader) {
        if (fragment_shader != 0) {
            throw std::runtime_error("Fragment shader already attached");
            glDeleteShader(fragment_shader);
        }
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &shader_code.source, nullptr);
        glCompileShader(fragment_shader);
    }
}

void Shader::update(const EventArgs& event_args) {
    if (dynamic_uniforms.setDynamic(event_args)) return;

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

// TODO: rework to work with uniforms.h
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
    dynamic_uniforms.passAllLights();
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

    initLightUniforms();
}

void Shader::initLightUniforms() {
    initLightUniform(dynamic_uniforms.point_loc, dynamic_uniforms.point_num_loc,
                     DynamicUniforms::point_varname, DynamicUniforms::point_num_varname,
                     DynamicUniforms::point_num_max, DynamicUniforms::point_parameter_count);
    initLightUniform(dynamic_uniforms.directional_loc, dynamic_uniforms.directional_num_loc,
                     DynamicUniforms::directional_varname, DynamicUniforms::directional_num_varname,
                     DynamicUniforms::directional_num_max, DynamicUniforms::directional_parameter_count);
    initLightUniform(dynamic_uniforms.spotlight_loc, dynamic_uniforms.spotlight_num_loc,
                     DynamicUniforms::spotlight_varname, DynamicUniforms::spotlight_num_varname,
                     DynamicUniforms::spotlight_num_max, DynamicUniforms::spotlight_parameter_count);
}

template <std::size_t SIZE>
void Shader::initLightUniform(std::array<int, SIZE>& uniform_locations, SHADER_UNIFORM_LOCATION& num_uniform_location,
                              const std::string& collection_name, const std::string& count_name,
                              int max_light_count, int light_param_count) {
    num_uniform_location = glGetUniformLocation(shader_program, count_name.c_str());
    if (num_uniform_location == -1) {
        printf("Uniform %s not found in %s shader - skipping light init.\n", count_name.c_str(), name.c_str());
        return;
    }

    for (int i = 0; i < max_light_count; i++) {
        auto p = PointLight::getParameterNames();
        for (int j = 0; j < light_param_count; j++) {
            std::string varname_element_name =
                    collection_name + "[" + std::to_string(i) + "]." + p[j];
            GLint loc = glGetUniformLocation(shader_program, varname_element_name.c_str());
            if (loc == -1)
                throw std::runtime_error("Uniform " + varname_element_name + " not found in " + name + " shader.");
            uniform_locations[i*light_param_count + j] = loc;
        }
    }

}

void Shader::updateMaterial(const EventArgs& event_args) {
    auto* material_payload = static_cast<const EventPayload<Material>*>(&event_args);
    this->material.value = material_payload->getPayload();
    this->material.is_dirty = true;
}

void Shader::passMaterialUniforms() {
    passUniform3fv("material.ambient", material.value.ambient);
    if (material.value.illuminated & ILLUMINATION::DIFFUSE)
        passUniform3fv("material.diffuse", material.value.diffuse);
    if (material.value.illuminated & ILLUMINATION::SPECULAR) {
        passUniform3fv("material.specular", material.value.specular);
        passUniform1f("material.shininess", material.value.shininess);
    }
    material.is_dirty = false;
}
