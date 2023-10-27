// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  2/10/2023

#include "drawable.h"

#include <utility>

DrawableObject::DrawableObject(const glm::vec3 &position, std::unique_ptr<Model>&& model,
                               std::string  shader_name) : position(position), shader_name(std::move(shader_name)), model(std::move(model)) {
    this->model_matrix = std::make_unique<TransformComposite>();
}

DrawableObject::~DrawableObject() {
//    this->model_matrix.reset();
//    this->model.reset();
}


void DrawableObject::draw() {
    EventArgs args {
            .payload = this->position,
            .type = EventType::S_TRANSLATION,
    };
    this->model_matrix->update(args);
    this->model->draw();
}

std::shared_ptr<glm::mat4> DrawableObject::getModelMatrix() const {
    return this->model_matrix->getMatrix();
}

std::shared_ptr<glm::mat3> DrawableObject::getNormalMatrix() const {
    return this->model_matrix->getNormalMatrix();
}

void DrawableObject::move(const glm::vec3 &delta) {
    this->position += delta;
    EventArgs args {
            .payload = delta,
            .type = EventType::U_TRANSLATION,
    };
    this->model_matrix->update(args);
}

void DrawableObject::rotate(const glm::vec3 &delta) {
    EventArgs args {
            .payload = delta,
            .type = EventType::U_ROTATION,
    };
    this->model_matrix->update(args);
}

void DrawableObject::scale(const glm::vec3 &delta) {
    EventArgs args {
            .payload = delta,
            .type = EventType::U_SCALE,
    };
    this->model_matrix->update(args);
}

void DrawableObject::passUniforms(Shader* shader) const {
    shader->passModelMatrix(*this->getModelMatrix());
    shader->passNormalMatrix(*this->getNormalMatrix());

    shader->passUniform3fv("object_color", this->object_color);
    shader->passUniform3fv("material.ambient", this->ambient);

    if (isIlluminated()) {
        shader->passUniform3fv("material.diffuse", this->material->diffuse);
        shader->passUniform3fv("material.specular", this->material->specular);
        shader->passUniform1f("material.shininess", this->material->shininess);
    }
}

void DrawableObject::setAmbient(const glm::vec3 &_ambient) {
    this->ambient = _ambient;
}

void DrawableObject::setProperties(const glm::vec3 &_diffuse, const glm::vec3 &_specular, float _shininess) {
    material = std::make_unique<Material>(_diffuse, _specular, _shininess);
}

void DrawableObject::setProperties(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular,
                                   float _shininess) {
    this->ambient = _ambient;
    material = std::make_unique<Material>(_diffuse, _specular, _shininess);
}

void DrawableObject::setColor(const glm::vec3 &color) {
    this->object_color = color;
}