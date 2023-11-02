// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  5/10/2023

#include "transform_composite.h"
#include "transform.h"

DynamicTransformComposite::DynamicTransformComposite() {
    this->components.push_back(std::make_shared<Translation>(glm::vec3(0.0f, 0.0f, 0.0f)));
    this->components.push_back(std::make_shared<Rotation>());
    this->components.push_back(std::make_shared<Scale>(glm::vec3(1.0f, 1.0f, 1.0f)));
}

DynamicTransformComposite::DynamicTransformComposite(const glm::vec3 &axis) {
    this->components.push_back(std::make_shared<Translation>(glm::vec3(0.0f, 0.0f, 0.0f)));
    this->components.push_back(std::make_shared<Rotation>());
    this->components.push_back(std::make_shared<RotationPoint>(axis));
    this->components.push_back(std::make_shared<Scale>(glm::vec3(1.0f, 1.0f, 1.0f)));
}


DynamicTransformComposite::DynamicTransformComposite(
        std::vector<std::shared_ptr<TransformationAbstract>> components) {
    for(auto & translation : components) {
        this->components.push_back(std::move(translation));
    }
}

const glm::mat4& DynamicTransformComposite::getMatrix() {
    if (this->is_dirty) {
        matrix = glm::mat4(1.0f);
        if (parent)
            matrix = parent->getMatrix();
        for(auto & component : this->components) {
            matrix = matrix * component->getMatrix();
        }
        normal_matrix = glm::mat3(glm::transpose(glm::inverse(glm::mat3(matrix))));
        this->is_dirty = false;
    }
    return this->matrix;
}

const glm::mat3& DynamicTransformComposite::getNormalMatrix() {
    if (this->is_dirty) {
        matrix = glm::mat4(1.0f);
        if (parent)
            matrix = parent->getMatrix();
        for(auto & component : this->components) {
            matrix = matrix * component->getMatrix();
        }
        normal_matrix = glm::mat3(glm::transpose(glm::inverse(glm::mat3(matrix))));
        this->is_dirty = false;
    }
    return this->normal_matrix;
}

void DynamicTransformComposite::update(const EventArgs &event_args) {
    for(auto & component : this->components) {
        component->update(event_args);
    }
    this->is_dirty = true;
}

void DynamicTransformComposite::setParent(std::shared_ptr<TransformationAbstract> component) {
    this->parent = std::move(component);
    this->is_dirty = true;
}