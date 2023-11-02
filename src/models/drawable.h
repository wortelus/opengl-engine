// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  2/10/2023

#ifndef ZPG_DRAWABLE_H
#define ZPG_DRAWABLE_H


#include <variant>
#include "glm/vec3.hpp"
#include "../transform/transform_composite.h"
#include "../util/observer.h"
#include "model.h"
#include "material.h"
#include "../util/const.h"

class DrawableObject : public ISubjectSingle {
private:
    glm::vec3 position;

    std::string shader_name;
    SHADER_ALIAS_DATATYPE shader_alias = 0;

    const Model* model;

    Material material;

    std::shared_ptr<DynamicTransformComposite> model_matrix;
public:
    DrawableObject(const glm::vec3& position, const Model* model, std::string shader_name);
    DrawableObject(const glm::vec3& position, const Model* model, std::string shader_name,
                   const glm::vec3& ambient);
    DrawableObject(const glm::vec3& position, const Model* model, std::string shader_name,
                   const glm::vec3& ambient, const glm::vec3& axis);
    ~DrawableObject() = default;

    std::shared_ptr<DynamicTransformComposite> getModelComposite() { return model_matrix; }
    void setModelParent(std::weak_ptr<DynamicTransformComposite> weak_parent);

    [[nodiscard]] const glm::mat4& getModelMatrix() const;
    [[nodiscard]] const glm::mat3& getNormalMatrix() const;

    [[nodiscard]] const std::string& getShaderName() const { return this->shader_name; }
    void assignShaderAlias(const SHADER_ALIAS_DATATYPE& alias) { this->shader_alias = alias; }
    [[nodiscard]] SHADER_ALIAS_DATATYPE getShaderAlias() const { return this->shader_alias; }

    void setTranslate(const glm::vec3& location);
    void translate(const glm::vec3& delta);

    void setRotate(const glm::vec3& rotation);
    void rotate(const glm::vec3& delta);

    void rotateAround(const float& delta, const glm::vec3& point);

    void setScale(const glm::vec3& scale);
    void scale(const glm::vec3& delta);

    void setAmbient(const glm::vec3& _ambient);
    void setDiffuse(const glm::vec3& _diffuse);
    void setProperties(const glm::vec3& _diffuse, const glm::vec3& _specular, float _shininess);
    void setProperties(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular, float _shininess);

    [[nodiscard]] const glm::vec3& getPosition() const { return this->position; }
    [[nodiscard]] const Material& getMaterial() const { return this->material; }

    void notifyModel();
    void notifyMaterial();
    void notifyModelParameters();

    void draw();
};


#endif //ZPG_DRAWABLE_H
