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
#include "material.h"
#include "../util/const.h"

class DrawableObject {
private:
    glm::vec3 position;
    std::string shader_name;

    std::unique_ptr<Model> model;

    glm::vec3 object_color = OBJECT_COLOR;
    glm::vec3 ambient = AMBIENT_LIGHT;
    std::unique_ptr<Material> material;

    std::unique_ptr<TransformComposite> model_matrix;
public:
    DrawableObject(const glm::vec3& position, std::unique_ptr<Model>&& model, std::string shader_name);
    ~DrawableObject();
    
    [[nodiscard]] std::shared_ptr<glm::mat4> getModelMatrix() const;
    [[nodiscard]] std::shared_ptr<glm::mat3> getNormalMatrix() const;

    [[nodiscard]] const std::string& getShaderName() const { return this->shader_name; }

    void move(const glm::vec3& delta);
    void rotate(const glm::vec3& delta);
    void scale(const glm::vec3& delta);

    void setColor(const glm::vec3& color);
    void setAmbient(const glm::vec3& _ambient);
    void setProperties(const glm::vec3& _diffuse, const glm::vec3& _specular, float _shininess);
    void setProperties(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular, float _shininess);
    [[nodiscard]] bool isIlluminated() const { return this->material != nullptr; }
    
    void passUniforms(Shader* shader) const;

    void draw();
};


#endif //ZPG_DRAWABLE_H
