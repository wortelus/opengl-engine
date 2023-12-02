// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  1/12/2023

#ifndef ZPG_LINEAR_H
#define ZPG_LINEAR_H


#include "animation.h"

class Linear : public Animation {
private:
    AnimationArgs args;
    const glm::vec3 a;
    const glm::vec3 u;
    const float max_distance;
    float t = 0.0f;
    float speed;
    std::unique_ptr<DrawableObject> object;
private:
    void translate();
public:
    Linear(std::unique_ptr<DrawableObject> object, glm::vec3 a, glm::vec3 u, float max_distance, float speed, AnimationArgs args);
    ~Linear() override = default;

    void step(float delta_time) override;
    void draw() override;

    const SHADER_ALIAS_DATATYPE getShaderAlias() override { return object->getShaderAlias(); }
    void attachShader(IObserver* new_observer) override { object->attach(new_observer); }
    void notifyShader() override { object->notifyModelParameters(); }

    DrawableObject& getDrawableObject() override { return *object; }
};


#endif //ZPG_LINEAR_H
