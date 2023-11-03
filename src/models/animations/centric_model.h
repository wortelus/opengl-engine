// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/10/2023

#ifndef ZPG_CENTRIC_MODEL_H
#define ZPG_CENTRIC_MODEL_H


#include <utility>
#include <functional>
#include <queue>

#include "../drawable.h"
#include "animation.h"

class CentricModelComponent : public Animation {
protected:
    glm::vec3 parent_center = glm::vec3(0.0f);
    float rotational_multiplier = 1.f;
    std::unique_ptr<DrawableObject> object;
public:
    explicit CentricModelComponent(std::unique_ptr<DrawableObject> object)
            : object(std::move(object)) { }

    ~CentricModelComponent() override = default;

    DrawableObject& getDrawableObject() override { return *object; }

    void setMultiplier(const float& axis) { this->rotational_multiplier = axis; }
    void setCenter(const glm::vec3& rotational_center) { this->parent_center = rotational_center; }

    void step(float delta_time) override;
    void draw() override { object->draw(); }

    const SHADER_ALIAS_DATATYPE getShaderAlias() override { return object->getShaderAlias(); }
    void attachShader(IObserver* new_observer) override { object->attach(new_observer); }
    void notifyShader() override { object->notifyModelParameters(); }
};

class CentricModelLeaf : public CentricModelComponent {
private:

public:
    explicit CentricModelLeaf(std::unique_ptr<DrawableObject> object)
            : CentricModelComponent(std::move(object)) {}

    ~CentricModelLeaf() override = default;
};

class CentricComposite : public CentricModelComponent {
private:
    std::vector<std::unique_ptr<CentricModelComponent>> children;
public:
    explicit CentricComposite(std::unique_ptr<DrawableObject> object)
            : CentricModelComponent(std::move(object)) {}

    ~CentricComposite() override = default;

    void addModel(std::unique_ptr<CentricModelComponent> model);

    void bfsTraverse(const std::function<void(CentricModelComponent*)>& func);
};


#endif //ZPG_CENTRIC_MODEL_H
