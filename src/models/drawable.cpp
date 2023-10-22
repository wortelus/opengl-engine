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
    shader->passUniform3fv("material.ambient", this->ambient);
    shader->passUniform3fv("material.diffuse", this->diffuse);
    shader->passUniform3fv("material.specular", this->specular);
    shader->passUniform1f("material.shininess", this->shininess);

}

void DrawableObject::setProperties(const glm::vec3 &_ambient, const glm::vec3 &_diffuse, const glm::vec3 &_specular,
                                   float _shininess) {
    this->ambient = _ambient;
    this->diffuse = _diffuse;
    this->specular = _specular;
    this->shininess = _shininess;

}
