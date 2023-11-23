// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  2/10/2023

#include "drawable.h"

#include <utility>
#include <stdexcept>

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

DrawableObject::DrawableObject(const glm::vec3& position,
                               const Model* model,
                               std::string shader_name,
                               const glm::vec3& ambient,
                               const glm::vec3& axis)
        : position(position),
          shader_name(std::move(shader_name)),
          model(model) {
    this->model_matrix = std::make_shared<DynamicTransformComposite>(axis);

    EventPayload<glm::vec3> payload{this->position, EventType::S_TRANSLATION};
    this->model_matrix->update(payload);

    this->material.ambient = ambient;
}


void DrawableObject::draw() const {
    if (this->interaction_id != 0)
        glStencilFunc(GL_ALWAYS, this->interaction_id, 0xFF);
    if (this->model->isTextured())
        this->material.texture->bind();
    this->model->draw();
}

void DrawableObject::setModelParent(std::weak_ptr<DynamicTransformComposite> weak_parent) {
    this->model_matrix->setParent(std::move(weak_parent));
}

const glm::mat4& DrawableObject::getModelMatrix() const {
    return this->model_matrix->getMatrix();
}

const glm::mat3& DrawableObject::getNormalMatrix() const {
    return this->model_matrix->getNormalMatrix();
}

void DrawableObject::setTranslate(const glm::vec3& location) {
    EventPayload<glm::vec3> payload{location, EventType::S_TRANSLATION};
    this->model_matrix->update(payload);
}


void DrawableObject::translate(const glm::vec3& delta) {
    EventPayload<glm::vec3> payload{delta, EventType::U_TRANSLATION};
    this->model_matrix->update(payload);
}

void DrawableObject::setRotate(const glm::vec3& rotation) {
    EventPayload<glm::vec3> payload{rotation, EventType::S_ROTATION};
    this->model_matrix->update(payload);
}

void DrawableObject::rotate(const glm::vec3& delta) {
    EventPayload<glm::vec3> payload{delta, EventType::U_ROTATION};
    this->model_matrix->update(payload);
}

void DrawableObject::rotateAround(const float& delta, const glm::vec3& point) {
    EventPayload<glm::vec3> point_payload{point, EventType::S_ROTATION_POINT_ORIGIN};
    this->model_matrix->update(point_payload);

    EventPayload<float> rotation_payload{delta, EventType::U_ROTATION_POINT_ANGLE};
    this->model_matrix->update(rotation_payload);

}

void DrawableObject::setScale(const glm::vec3& scale) {
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

void DrawableObject::setDiffuse(const glm::vec3& _diffuse) {
    this->material.diffuse = _diffuse;
    if (material.illuminated == ILLUMINATION::AMBIENT) {
        material.illuminated = ILLUMINATION::DIFFUSE;
    }
}

void DrawableObject::notifyModel() const {
    notify(EventPayload<const glm::mat4*>{&this->model_matrix->getMatrix(),
                                          EventType::U_MODEL_MATRIX});

    notify(EventPayload<const glm::mat3*>{&this->model_matrix->getNormalMatrix(),
                                          EventType::U_NORMAL_MATRIX});
}

void DrawableObject::notifyMaterial() const {
    notify(EventPayload<const Material*>{&this->material, EventType::U_MATERIAL});
    if (this->model->isTextured()) {
        notify(EventPayload<TEXTURE_UNIT>{this->material.texture->getTextureUnit(),
                                                 EventType::U_TEXTURE_UNIT});
    }
}

void DrawableObject::notifyModelParameters() const {
    notifyModel();
    notifyMaterial();
}

void DrawableObject::assignTexture(const Texture* texture) {
    this->material.texture = texture;
}

void DrawableObject::setInteractionID(const char& id) {
    if (this->interaction_id != 0)
        throw std::runtime_error("Interaction ID already set");
    interaction_id = id;
}

char DrawableObject::getInteractionID() const {
    if (!this->isInteract())
        throw std::runtime_error("Object is not interactive.");
    if (this->interaction_id == 0)
        throw std::runtime_error("Interaction ID not set.");
    return this->interaction_id;
}
