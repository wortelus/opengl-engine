// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  2/10/2023

#include "drawable.h"

#include <utility>

DrawableObject::DrawableObject(const glm::vec3& position, const Model* model,
                               std::string shader_name)
                               : position(position),
                               shader_name(std::move(shader_name)),
                               model(model) {
    this->model_matrix = std::make_shared<DynamicTransformComposite>();

    EventPayload<glm::vec3> payload{this->position, EventType::S_TRANSLATION};
    this->model_matrix->update(payload);
}

DrawableObject::DrawableObject(const glm::vec3& position,
                               const Model* model,
                               std::string shader_name,
                               const glm::vec3& ambient)
                               : position(position),
                               shader_name(std::move(shader_name)),
                               model(model) {
    this->model_matrix = std::make_shared<DynamicTransformComposite>();

    EventPayload<glm::vec3> payload{this->position, EventType::S_TRANSLATION};
    this->model_matrix->update(payload);

    this->material.ambient = ambient;
}

DrawableObject::DrawableObject(const glm::vec3 &position,
                               const Model* model,
                               std::string shader_name,
                               const glm::vec3 &ambient,
                               const glm::vec3 &axis)
                               : position(position),
                               shader_name(std::move(shader_name)),
                               model(model) {
    this->model_matrix = std::make_shared<DynamicTransformComposite>(axis);

    EventPayload<glm::vec3> payload{this->position, EventType::S_TRANSLATION};
    this->model_matrix->update(payload);

    this->material.ambient = ambient;
}

DrawableObject::~DrawableObject() {
//    this->model_matrix.reset();
//    this->model.reset();
}


void DrawableObject::draw() {
    this->model->draw();
}

const glm::mat4& DrawableObject::getModelMatrix() const {
    return this->model_matrix->getMatrix();
}

const glm::mat3& DrawableObject::getNormalMatrix() const {
    return this->model_matrix->getNormalMatrix();
}

void DrawableObject::setLocation(const glm::vec3 &location) {
    EventPayload<glm::vec3> payload{location, EventType::S_TRANSLATION};
    this->model_matrix->update(payload);
}


void DrawableObject::move(const glm::vec3& delta) {
    EventPayload<glm::vec3> payload{delta, EventType::U_TRANSLATION};
    this->model_matrix->update(payload);
}

void DrawableObject::rotate(const glm::vec3& delta) {
    EventPayload<glm::vec3> payload{delta, EventType::U_ROTATION};
    this->model_matrix->update(payload);
}

void DrawableObject::setScale(const glm::vec3 &scale) {
    EventPayload<glm::vec3> payload{scale, EventType::S_SCALE};
    this->model_matrix->update(payload);
}

void DrawableObject::scale(const glm::vec3& delta) {
    EventPayload<glm::vec3> payload{delta, EventType::U_SCALE};
    this->model_matrix->update(payload);
}

void DrawableObject::setAmbient(const glm::vec3& _ambient) {
    this->material.ambient = _ambient;
}

void DrawableObject::setProperties(const glm::vec3& _diffuse, const glm::vec3& _specular, float _shininess) {
    material.diffuse = _diffuse;
    material.specular = _specular;
    material.shininess = _shininess;
    material.illuminated = ILLUMINATION::ALL;
}

void DrawableObject::setProperties(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular,
                                   float _shininess) {
    material.ambient = _ambient;
    material.diffuse = _diffuse;
    material.specular = _specular;
    material.shininess = _shininess;
    material.illuminated = ILLUMINATION::ALL;
}

void DrawableObject::setDiffuse(const glm::vec3 &_diffuse) {
    this->material.diffuse = _diffuse;
    if (material.illuminated == ILLUMINATION::AMBIENT) {
        material.illuminated = ILLUMINATION::DIFFUSE;
    }
}

void DrawableObject::notifyModel() {
    EventPayload<glm::mat4> model_mat = {this->model_matrix->getMatrix(), EventType::U_MODEL_MATRIX};
    notify(model_mat);

    EventPayload<glm::mat3> normal_mat = {this->model_matrix->getNormalMatrix(),
                                                           EventType::U_NORMAL_MATRIX};
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

void DrawableObject::rotateAround(const float& delta, const glm::vec3& point) {
    EventPayload<glm::vec3> point_payload {point, EventType::S_ROTATION_POINT_ORIGIN};
    this->model_matrix->update(point_payload);

    EventPayload<float> rotation_payload{delta, EventType::U_ROTATION_POINT_ANGLE};
    this->model_matrix->update(rotation_payload);

}

void DrawableObject::setModelParent(std::shared_ptr<DynamicTransformComposite> parent) {
    this->model_matrix->setParent(std::move(parent));
}