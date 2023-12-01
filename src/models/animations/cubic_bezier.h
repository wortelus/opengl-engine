// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  27/11/2023

#ifndef ZPG_CUBIC_BEZIER_H
#define ZPG_CUBIC_BEZIER_H


#include "animation.h"

class CubicBezier : public Animation {
private:
    static constexpr glm::mat4 bezier_coefficients = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
                                              glm::vec4(3.0, -6.0, 3.0, 0),
                                              glm::vec4(-3.0, 3.0, 0, 0),
                                              glm::vec4(1, 0, 0, 0));
    AnimationArgs args;
    const glm::mat4x3 control_points;
    float t = 0.0f;
    float speed;
    std::unique_ptr<DrawableObject> object;
private:
    void translate();
public:
    CubicBezier(std::unique_ptr<DrawableObject> object, glm::mat4x3 control_points, float speed, AnimationArgs args);
    ~CubicBezier() override = default;

    void step(float delta_time) override;
    void draw() override;

    const SHADER_ALIAS_DATATYPE getShaderAlias() override { return object->getShaderAlias(); }
    void attachShader(IObserver* new_observer) override { object->attach(new_observer); }
    void notifyShader() override { object->notifyModelParameters(); }

    DrawableObject& getDrawableObject() override { return *object; }
};


#endif //ZPG_CUBIC_BEZIER_H
