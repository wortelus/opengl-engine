// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  2/10/2023

#include "transform.h"
#include "glm/ext/matrix_transform.hpp"

Translation::Translation(const glm::vec3 &initial_translation) : translation(initial_translation) {
    this->matrix = glm::translate(glm::mat4(1.0), this->translation);
}

const glm::mat4& Translation::GetMatrix() {
    return this->matrix;
}

void Translation::MoveBy(const glm::vec3 &offset) {
    this->translation += offset;
    this->matrix = glm::translate(glm::mat4(1.0), this->translation);
}

void Translation::SetTranslation(const glm::vec3 &new_translation) {
    this->translation = new_translation;
    this->matrix = glm::translate(glm::mat4(1.0), this->translation);
}

void Translation::Update(const EventArgs &event_args) {
    if (event_args.type == EventType::U_TRANSLATION) {
        this->MoveBy(event_args.payload);
    } else if (event_args.type == EventType::S_TRANSLATION) {
        this->SetTranslation(event_args.payload);
    }
    // TODO: log invalid operation
}

Rotation::Rotation() : origin(glm::vec3(1.0f, 0.0f, 0.0f)), rotation(glm::vec3(0.0f, 0.0f, 0.0f)) {
    this->matrix = glm::rotate(glm::mat4(1.0), .0f, this->origin);
}

Rotation::Rotation(const glm::vec3 &initial_origin) : origin(initial_origin), rotation(glm::vec3(0.0f, 0.0f, 0.0f)) {
    this->matrix = glm::rotate(glm::mat4(1.0), .0f, this->origin);
}

void Rotation::RotateBy(const glm::vec3 &offset) {
    this->rotation += offset;
    if (offset.x != 0.0f) {
        this->matrix = glm::rotate(this->matrix, glm::radians(offset.x), glm::vec3(1.0f, 0.0f, 0.0f));
    } else if (offset.y != 0.0f) {
        this->matrix = glm::rotate(this->matrix, glm::radians(offset.y), glm::vec3(0.0f, 1.0f, 0.0f));
    } else if (offset.z != 0.0f) {
        this->matrix = glm::rotate(this->matrix, glm::radians(offset.z), glm::vec3(0.0f, 0.0f, 1.0f));
    }
}

void Rotation::SetRotation(const glm::vec3 &new_rotation) {
    this->rotation.x = glm::radians(new_rotation.x);
    this->rotation.y = glm::radians(new_rotation.y);
    this->rotation.z = glm::radians(new_rotation.z);
}

const glm::mat4& Rotation::GetMatrix() {
    return this->matrix;
}

void Rotation::Update(const EventArgs &event_args) {
    if (event_args.type == EventType::U_ROTATION) {
        this->RotateBy(event_args.payload);
    } else if (event_args.type == EventType::S_ROTATION) {
        this->SetRotation(event_args.payload);
    }
}

Scale::Scale(const glm::vec3 &initial_scale) : scale(initial_scale) {
    this->matrix = glm::scale(glm::mat4(1.0), this->scale);
}

void Scale::SetScale(const glm::vec3 &new_scale) {
    this->scale = new_scale;
    matrix = glm::scale(glm::mat4(1.0), this->scale);
}

void Scale::ScaleBy(const glm::vec3 &offset) {
    this->scale += offset;
    matrix = glm::scale(glm::mat4(1.0), this->scale);
}

const glm::mat4& Scale::GetMatrix() {
    return this->matrix;
}

void Scale::Update(const EventArgs &event_args) {
    if (event_args.type == EventType::U_SCALE) {
        this->ScaleBy(event_args.payload);
    } else if (event_args.type == EventType::S_SCALE) {
        this->SetScale(event_args.payload);
    }
}
