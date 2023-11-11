// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  28/10/2023

#include "shader_uniforms.h"
#include "glm/gtc/type_ptr.hpp"
#include "uniforms.h"

void ShaderUniforms::passEvent(const EventArgs& event_args) {
    switch (event_args.type) {
        case EventType::U_MODEL_MATRIX: {
            const auto* model_matrix = static_cast<const EventPayload<const glm::mat4*>*>(&event_args);
            model.value = model_matrix->getPayload();
            model.is_dirty = true;
            break;
        }
        case EventType::U_VIEW_MATRIX: {
            const auto* view_matrix = static_cast<const EventPayload<const glm::mat4*>*>(&event_args);
            view.value = view_matrix->getPayload();
            view.is_dirty = true;
            break;
        }
        case EventType::U_PROJECTION_MATRIX: {
            const auto* projection_matrix = static_cast<const EventPayload<const glm::mat4*>*>(&event_args);
            projection.value = projection_matrix->getPayload();
            projection.is_dirty = true;
            break;
        }
        case EventType::U_NORMAL_MATRIX: {
            const auto* normal_matrix = static_cast<const EventPayload<const glm::mat3*>*>(&event_args);
            normal.value = normal_matrix->getPayload();
            normal.is_dirty = true;
            break;
        }
        case EventType::U_CAMERA_POSITION: {
            const auto* camera_pos = static_cast<const EventPayload<const glm::vec3*>*>(&event_args);
            camera_position.value = camera_pos->getPayload();
            camera_position.is_dirty = true;
            break;
        }
        case EventType::U_TEXTURE_UNIT: {
            const auto* tex_unit = static_cast<const EventPayload<TEXTURE_UNIT>*>(&event_args);
            if (tex_unit->getPayload() == this->texture_unit.value)
                break; // no need to update
            this->texture_unit.value = tex_unit->getPayload();
            this->texture_unit.is_dirty = true;
            break;
        }
        default:
            break;
    }
}

void ShaderUniforms::lazyPassUniforms() {
    if (model.is_dirty) {
        Uniforms::passUniformMatrix4fv(model.location, *model.value);
        model.is_dirty = false;
    }
    if (view.is_dirty) {
        Uniforms::passUniformMatrix4fv(view.location, *view.value);
        view.is_dirty = false;
    }
    if (projection.is_dirty) {
        Uniforms::passUniformMatrix4fv(projection.location, *projection.value);
        projection.is_dirty = false;
    }
    if (normal.is_dirty) {
        Uniforms::passUniformMatrix3fv(normal.location, *normal.value);
        normal.is_dirty = false;
    }
    if (camera_position.is_dirty) {
        Uniforms::passUniform3fv(camera_position.location, *camera_position.value);
        camera_position.is_dirty = false;
    }
    if (texture_unit.is_dirty) {
        Uniforms::passUniform1i(texture_unit.location, static_cast<GLint>(texture_unit.value));
        texture_unit.is_dirty = false;
    }
}