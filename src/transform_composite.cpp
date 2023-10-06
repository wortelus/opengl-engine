//
// Created by wortelus on 5.10.23.
//

#include "transform_composite.h"
#include "transform.h"

TransformComposite::TransformComposite() {
    // initializing model matrix
    // translation
    translation = std::make_unique<Translation>(glm::vec3(0.0f, 0.0f, 0.0f));
    // rotation
    rotation = std::make_unique<Rotation>();
    // scale
    scale = std::make_unique<Scale>(glm::vec3(1.0f, 1.0f, 1.0f));

    // initializing model matrix
    model_matrix = std::make_unique<glm::mat4>(translation->GetMatrix() * rotation->GetMatrix() * scale->GetMatrix());
}

const glm::mat4& TransformComposite::GetMatrix() {
    if (!is_dirty) {
        return *model_matrix;
    }

    // recalculation
    model_matrix = std::make_unique<glm::mat4>(translation->GetMatrix() * rotation->GetMatrix() * scale->GetMatrix());
    is_dirty = false;

    return *model_matrix;
}

void TransformComposite::Update(const EventArgs &event_args) {
    if (event_args.type == EventType::U_TRANSLATION || event_args.type == EventType::S_TRANSLATION) {
        translation->Update(event_args);
    } else if (event_args.type == EventType::U_ROTATION || event_args.type == EventType::S_ROTATION) {
        rotation->Update(event_args);
    } else if (event_args.type == EventType::U_SCALE || event_args.type == EventType::S_SCALE) {
        scale->Update(event_args);
    }
    is_dirty = true;
}
