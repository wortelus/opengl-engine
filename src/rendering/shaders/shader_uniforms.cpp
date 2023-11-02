// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  28/10/2023

#include "shader_uniforms.h"

void ShaderUniforms::passEvent(const EventArgs& event_args) {
    switch (event_args.type) {
        case EventType::U_MODEL_MATRIX: {
            const auto* model_matrix = static_cast<const EventPayload<const glm::mat4&>*>(&event_args);
            model.value = &model_matrix->getPayload();
            model.is_dirty = true;
            break;
        }
        case EventType::U_VIEW_MATRIX: {
            const auto* view_matrix = static_cast<const EventPayload<const glm::mat4&>*>(&event_args);
            view.value = &view_matrix->getPayload();
            view.is_dirty = true;
            break;
        }
        case EventType::U_PROJECTION_MATRIX: {
            const auto* projection_matrix = static_cast<const EventPayload<const glm::mat4&>*>(&event_args);
            projection.value = &projection_matrix->getPayload();
            projection.is_dirty = true;
            break;
        }
        case EventType::U_NORMAL_MATRIX: {
            const auto* normal_matrix = static_cast<const EventPayload<const glm::mat3&>*>(&event_args);
            normal.value = &normal_matrix->getPayload();
            normal.is_dirty = true;
            break;
        }
        case EventType::U_CAMERA_POSITION: {
            const auto* camera_pos = static_cast<const EventPayload<const glm::vec3&>*>(&event_args);
            camera_position.value = &camera_pos->getPayload();
            camera_position.is_dirty = true;
            break;
        }
        default:
            break;
    }
}

void ShaderUniforms::updateUniforms() {
    if (model.is_dirty) {
        passUniformMatrix4fv(model.location, *model.value);
        model.is_dirty = false;
    }
    if (view.is_dirty) {
        passUniformMatrix4fv(view.location, *view.value);
        view.is_dirty = false;
    }
    if (projection.is_dirty) {
        passUniformMatrix4fv(projection.location, *projection.value);
        projection.is_dirty = false;
    }
    if (normal.is_dirty) {
        passUniformMatrix3fv(normal.location, *normal.value);
        normal.is_dirty = false;
    }
    if (camera_position.is_dirty) {
        passUniform3fv(camera_position.location, *camera_position.value);
        camera_position.is_dirty = false;
    }
}

void ShaderUniforms::passUniform1i(GLint location, GLint value) {
    glUniform1i(location, value);
}

void ShaderUniforms::passUniform1f(GLint location, GLfloat value) {
    glUniform1f(location, value);
}

void ShaderUniforms::passUniform3fv(GLint location, const glm::vec3& value) {
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void ShaderUniforms::passUniform4fv(GLint location, const glm::vec4& value) {
    glUniform4fv(location, 1, glm::value_ptr(value));

}

void ShaderUniforms::passUniformMatrix3fv(GLint location, const glm::mat3& value) {
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderUniforms::passUniformMatrix4fv(GLint location, const glm::mat4& value) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
