// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  2/12/2023

#ifndef ZPG_CUBIC_CHAIN_H
#define ZPG_CUBIC_CHAIN_H


#include "animation.h"

class CubicChain : public Animation {
private:
    AnimationArgs args;

    int current_control_point = 0;
    std::vector<glm::vec3> control_points;

    float t = 0.0f;
    float speed;
    std::unique_ptr<DrawableObject> object;
private:
    void translate();
public:
    CubicChain(std::unique_ptr<DrawableObject> object, const glm::vec3 initial_position, float speed, AnimationArgs args);
    ~CubicChain() override = default;

    void addControlPoint(glm::mat3x3 control_point);

    void step(float delta_time) override;
    void draw() override;

    const SHADER_ALIAS_DATATYPE getShaderAlias() override { return object->getShaderAlias(); }
    void attachShader(IObserver* new_observer) override { object->attach(new_observer); }
    void notifyShader() override { object->notifyModelParameters(); }

    DrawableObject& getDrawableObject() override { return *object; }
};


#endif //ZPG_CUBIC_CHAIN_H
