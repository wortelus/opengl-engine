// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  5/10/2023

#include "transform_composite.h"
#include "transform.h"

//
// TransformComposite
//

TransformComposite::TransformComposite() {
    // initializing model matrix
    // translation
    translation = std::make_unique<Translation>(glm::vec3(0.0f, 0.0f, 0.0f));
    // rotation
    rotation = std::make_unique<Rotation>();
    // scale
    scale = std::make_unique<Scale>(glm::vec3(1.0f, 1.0f, 1.0f));

    // initializing model matrix
    matrix = std::make_unique<glm::mat4>(*translation->getMatrix() * *rotation->getMatrix() * *scale->getMatrix());
    normal_matrix = std::make_shared<glm::mat3>(glm::transpose(glm::inverse(glm::mat3(*matrix))));
}

std::shared_ptr<glm::mat4> TransformComposite::getMatrix() {
    if (this->is_dirty) {
        matrix = std::make_unique<glm::mat4>(*translation->getMatrix() * *rotation->getMatrix() * *scale->getMatrix());
        normal_matrix = std::make_shared<glm::mat3>(glm::transpose(glm::inverse(glm::mat3(*matrix))));
        this->is_dirty = false;
    }
    return matrix;
}

void TransformComposite::update(const EventArgs& event_args) {
    if (event_args.type == EventType::U_TRANSLATION || event_args.type == EventType::S_TRANSLATION) {
        translation->update(event_args);
    } else if (event_args.type == EventType::U_ROTATION || event_args.type == EventType::S_ROTATION) {
        rotation->update(event_args);
    } else if (event_args.type == EventType::U_SCALE || event_args.type == EventType::S_SCALE) {
        scale->update(event_args);
    }
    this->is_dirty = true;
}

std::shared_ptr<glm::mat3> TransformComposite::getNormalMatrix() {
    if (this->is_dirty) {
        matrix = std::make_unique<glm::mat4>(*translation->getMatrix() * *rotation->getMatrix() * *scale->getMatrix());
        normal_matrix = std::make_shared<glm::mat3>(glm::transpose(glm::inverse(glm::mat3(*matrix))));
        this->is_dirty = false;
    }
    return normal_matrix;
}

//
// DynamicTransformComposite
//

DynamicTransformComposite::DynamicTransformComposite() {
    this->components.push_back(std::make_unique<Translation>(glm::vec3(0.0f, 0.0f, 0.0f)));
    this->components.push_back(std::make_unique<Rotation>());
    this->components.push_back(std::make_unique<Scale>(glm::vec3(1.0f, 1.0f, 1.0f)));
}

DynamicTransformComposite::DynamicTransformComposite(const glm::vec3 &axis) {
    this->components.push_back(std::make_unique<Translation>(glm::vec3(0.0f, 0.0f, 0.0f)));
    this->components.push_back(std::make_unique<Rotation>());
    this->components.push_back(std::make_unique<RotationPoint>(axis));
    this->components.push_back(std::make_unique<Scale>(glm::vec3(1.0f, 1.0f, 1.0f)));
}


DynamicTransformComposite::DynamicTransformComposite(
        std::vector<std::unique_ptr<TransformationAbstract>> components) {
    for(auto & translation : components) {
        this->components.push_back(std::move(translation));
    }
}

std::shared_ptr<glm::mat4> DynamicTransformComposite::getMatrix() {
    if (this->is_dirty) {
        matrix = std::make_unique<glm::mat4>(1.0f);
        for(auto & component : this->components) {
            *matrix = *matrix * *component->getMatrix();
        }
        normal_matrix = std::make_shared<glm::mat3>(glm::transpose(glm::inverse(glm::mat3(*matrix))));
        this->is_dirty = false;
    }
    return matrix;
}

std::shared_ptr<glm::mat3> DynamicTransformComposite::getNormalMatrix() {
    if (this->is_dirty) {
        matrix = std::make_unique<glm::mat4>(1.0f);
        for(auto & component : this->components) {
            *matrix = *matrix * *component->getMatrix();
        }
        normal_matrix = std::make_shared<glm::mat3>(glm::transpose(glm::inverse(glm::mat3(*matrix))));
        this->is_dirty = false;
    }
    return normal_matrix;
}

void DynamicTransformComposite::update(const EventArgs &event_args) {
    for(auto & component : this->components) {
        component->update(event_args);
    }
    this->is_dirty = true;
}