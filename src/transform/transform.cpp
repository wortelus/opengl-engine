// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  2/10/2023

#include "transform.h"
#include "glm/ext/matrix_transform.hpp"

Translation::Translation(const glm::vec3& initial_translation) : translation(initial_translation) {
    this->matrix = std::make_shared<glm::mat4>(glm::translate(glm::mat4(1.0), this->translation));
}

std::shared_ptr<glm::mat4> Translation::getMatrix() {
    if (this->is_dirty) {
        this->matrix = std::make_shared<glm::mat4>(glm::translate(glm::mat4(1.0), this->translation));
        this->is_dirty = false;
    }
    return this->matrix;
}

void Translation::moveBy(const glm::vec3& offset) {
    this->translation += offset;
    this->is_dirty = true;
}

void Translation::setTranslation(const glm::vec3& new_translation) {
    this->translation = new_translation;
    this->is_dirty = true;
}

void Translation::update(const EventArgs& event_args) {
    const auto* uniform = static_cast<const EventPayload<glm::vec3>*>(&event_args);

    if (event_args.type == EventType::U_TRANSLATION) {
        this->moveBy(uniform->getPayload());
    } else if (event_args.type == EventType::S_TRANSLATION) {
        this->setTranslation(uniform->getPayload());
    }
    // TODO: log invalid operation
}

Rotation::Rotation() : origin(glm::vec3(1.0f, 0.0f, 0.0f)), rotation(glm::vec3(0.0f, 0.0f, 0.0f)) {
    this->matrix = std::make_shared<glm::mat4>(glm::rotate(glm::mat4(1.0), .0f, this->origin));
}

Rotation::Rotation(const glm::vec3& initial_origin) : origin(initial_origin), rotation(glm::vec3(0.0f, 0.0f, 0.0f)) {
    this->matrix = std::make_shared<glm::mat4>(glm::rotate(glm::mat4(1.0), .0f, this->origin));
}

void Rotation::rotateBy(const glm::vec3& offset) {
    this->rotation += offset;
    this->is_dirty = true;
}

void Rotation::setRotation(const glm::vec3& new_rotation) {
    this->rotation.x = new_rotation.x;
    this->rotation.y = new_rotation.y;
    this->rotation.z = new_rotation.z;
    this->is_dirty = true;
}

std::shared_ptr<glm::mat4> Rotation::getMatrix() {
    if (this->is_dirty) {
        this->matrix = std::make_shared<glm::mat4>(
                glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.x), glm::vec3(1.0, 0.0, 0.0)) *
                glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.y), glm::vec3(0.0, 1.0, 0.0)) *
                glm::rotate(glm::mat4(1.0), glm::radians(this->rotation.z), glm::vec3(0.0, 0.0, 1.0)));
        this->is_dirty = false;
    }
    return this->matrix;
}

void Rotation::update(const EventArgs& event_args) {
    const auto* uniform = static_cast<const EventPayload<glm::vec3>*>(&event_args);
    if (event_args.type == EventType::U_ROTATION) {
        this->rotateBy(uniform->getPayload());
    } else if (event_args.type == EventType::S_ROTATION) {
        this->setRotation(uniform->getPayload());
    }
}

Scale::Scale(const glm::vec3& initial_scale) : scale(initial_scale) {
    this->matrix = std::make_shared<glm::mat4>(glm::scale(glm::mat4(1.0), this->scale));
}

void Scale::scaleBy(const glm::vec3& offset) {
    this->scale += offset;
    this->is_dirty = true;
}

void Scale::setScale(const glm::vec3& new_scale) {
    this->scale = new_scale;
    this->is_dirty = true;
}

std::shared_ptr<glm::mat4> Scale::getMatrix() {
    if (this->is_dirty) {
        matrix = std::make_shared<glm::mat4>(glm::scale(glm::mat4(1.0), this->scale));
        this->is_dirty = false;
    }
    return this->matrix;
}

void Scale::update(const EventArgs& event_args) {
    const auto* uniform = static_cast<const EventPayload<glm::vec3>*>(&event_args);
    if (event_args.type == EventType::U_SCALE) {
        this->scaleBy(uniform->getPayload());
    } else if (event_args.type == EventType::S_SCALE) {
        this->setScale(uniform->getPayload());
    }
}
