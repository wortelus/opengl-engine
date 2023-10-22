// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  2/10/2023

#ifndef ZPG_DRAWABLE_H
#define ZPG_DRAWABLE_H


#include "glm/vec3.hpp"
#include "../transform/transform_composite.h"
#include "../util/observer.h"
#include "model.h"
#include "../rendering/shader.h"

class DrawableObject {
private:
    glm::vec3 position;
    std::unique_ptr<TransformComposite> model_matrix;
    std::unique_ptr<Model> model;
    std::string shader_name;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
public:
    DrawableObject(const glm::vec3& position, std::unique_ptr<Model>&& model, std::string shader_name);
    ~DrawableObject();

    [[nodiscard]] const glm::vec3& GetPosition() const { return this->position; }

    [[nodiscard]] std::shared_ptr<glm::mat4> getModelMatrix() const;
    [[nodiscard]] const std::string& getShaderName() const { return this->shader_name; }

    void move(const glm::vec3& delta);
    void rotate(const glm::vec3& delta);
    void scale(const glm::vec3& delta);

    void setProperties(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular, float _shininess);
    void passUniforms(Shader* shader) const;

    void draw();
};


#endif //ZPG_DRAWABLE_H
