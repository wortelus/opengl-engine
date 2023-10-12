// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  2/10/2023

#include "transform.h"
#include "glm/ext/matrix_transform.hpp"

Translation::Translation(const glm::vec3 &initial_translation) : translation(initial_translation) {
    this->matrix = glm::translate(glm::mat4(1.0), this->translation);
}

const glm::mat4& Translation::getMatrix() {
    return this->matrix;
}

void Translation::moveBy(const glm::vec3 &translation) {
    this->translation += translation;
    this->matrix = glm::translate(glm::mat4(1.0), this->translation);
}

void Translation::setTranslation(const glm::vec3 &translation) {
    this->translation = translation;
    this->matrix = glm::translate(glm::mat4(1.0), this->translation);
}

void Translation::update(const EventArgs &event_args) {
    if (event_args.type == EventType::U_TRANSLATION) {
        this->moveBy(event_args.payload);
    } else if (event_args.type == EventType::S_TRANSLATION) {
        this->setTranslation(event_args.payload);
    }
    // TODO: log invalid operation
}

Rotation::Rotation() : origin(glm::vec3(1.0f, 0.0f, 0.0f)), rotation(glm::vec3(0.0f, 0.0f, 0.0f)) {
    this->matrix = glm::rotate(glm::mat4(1.0), .0f, this->origin);
}

Rotation::Rotation(const glm::vec3 &initial_origin) : origin(initial_origin), rotation(glm::vec3(0.0f, 0.0f, 0.0f)) {
    this->matrix = glm::rotate(glm::mat4(1.0), .0f, this->origin);
}

void Rotation::rotateBy(const glm::vec3 &rotation) {
    this->rotation += rotation;
    if (rotation.x != 0.0f) {
        this->matrix = glm::rotate(this->matrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    } else if (rotation.y != 0.0f) {
        this->matrix = glm::rotate(this->matrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    } else if (rotation.z != 0.0f) {
        this->matrix = glm::rotate(this->matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    }
}

void Rotation::setRotation(const glm::vec3 &rotation) {
    this->rotation.x = glm::radians(rotation.x);
    this->rotation.y = glm::radians(rotation.y);
    this->rotation.z = glm::radians(rotation.z);
}

const glm::mat4& Rotation::getMatrix() {
    return this->matrix;
}

void Rotation::update(const EventArgs &event_args) {
    if (event_args.type == EventType::U_ROTATION) {
        this->rotateBy(event_args.payload);
    } else if (event_args.type == EventType::S_ROTATION) {
        this->setRotation(event_args.payload);
    }
}

Scale::Scale(const glm::vec3 &initial_scale) : scale(initial_scale) {
    this->matrix = glm::scale(glm::mat4(1.0), this->scale);
}

void Scale::setScale(const glm::vec3 &scale) {
    this->scale = scale;
    matrix = glm::scale(glm::mat4(1.0), this->scale);
}

void Scale::scaleBy(const glm::vec3 &scale) {
    this->scale += scale;
    matrix = glm::scale(glm::mat4(1.0), this->scale);
}

const glm::mat4& Scale::getMatrix() {
    return this->matrix;
}

void Scale::update(const EventArgs &event_args) {
    if (event_args.type == EventType::U_SCALE) {
        this->scaleBy(event_args.payload);
    } else if (event_args.type == EventType::S_SCALE) {
        this->setScale(event_args.payload);
    }
}
