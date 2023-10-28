// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  2/10/2023

#include "drawable.h"

#include <utility>

DrawableObject::DrawableObject(const glm::vec3 &position, std::unique_ptr<Model>&& model,
                               std::string  shader_name)
                               : position(position), shader_name(std::move(shader_name)), model(std::move(model)) {
    this->model_matrix = std::make_unique<TransformComposite>();

    EventPayload<glm::vec3> payload {this->position, EventType::S_TRANSLATION};
    this->model_matrix->update(payload);
}

DrawableObject::DrawableObject(const glm::vec3 &position, std::unique_ptr<Model> &&model, std::string shader_name,
                               const glm::vec3 &ambient)
                               : position(position), shader_name(std::move(shader_name)), model(std::move(model)) {
    this->model_matrix = std::make_unique<TransformComposite>();

    EventPayload<glm::vec3> payload {this->position, EventType::S_TRANSLATION};
    this->model_matrix->update(payload);
}

DrawableObject::~DrawableObject() {
//    this->model_matrix.reset();
//    this->model.reset();
}


void DrawableObject::draw() {
    this->model->draw();
}

std::shared_ptr<glm::mat4> DrawableObject::getModelMatrix() const {
    return this->model_matrix->getMatrix();
}

std::shared_ptr<glm::mat3> DrawableObject::getNormalMatrix() const {
    return this->model_matrix->getNormalMatrix();
}

void DrawableObject::move(const glm::vec3 &delta) {
    EventPayload<glm::vec3> payload {delta, EventType::U_TRANSLATION};
    this->model_matrix->update(payload);
}

void DrawableObject::rotate(const glm::vec3 &delta) {
    EventPayload<glm::vec3> payload {delta, EventType::U_ROTATION};
    this->model_matrix->update(payload);
}

void DrawableObject::scale(const glm::vec3 &delta) {
    EventPayload<glm::vec3> payload {delta, EventType::U_SCALE};
    this->model_matrix->update(payload);
}

void DrawableObject::setAmbient(const glm::vec3 &_ambient) {
    this->material.ambient = _ambient;
}

void DrawableObject::setProperties(const glm::vec3 &_diffuse, const glm::vec3 &_specular, float _shininess) {
    material = Material(_diffuse, _specular, _shininess);
}

void DrawableObject::setProperties(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular,
                                   float _shininess) {
    material = Material(_ambient, _diffuse, _specular, _shininess);
}

void DrawableObject::setColor(const glm::vec3 &color) {
    this->material.object_color = color;
}

void DrawableObject::notifyModel() {
    EventPayload<std::shared_ptr<glm::mat4>> model_mat = {this->model_matrix->getMatrix(), EventType::U_MODEL_MATRIX};
    notify(model_mat);

    EventPayload<std::shared_ptr<glm::mat3>> normal_mat = {this->model_matrix->getNormalMatrix(), EventType::U_NORMAL_MATRIX};
    notify(normal_mat);
}

void DrawableObject::notifyMaterial() {
    EventPayload<Material> material_payload = {this->material, EventType::U_MATERIAL};
    notify(material_payload);
}

void DrawableObject::notifyModelParameters() {
    notifyModel();
    notifyMaterial();
}
