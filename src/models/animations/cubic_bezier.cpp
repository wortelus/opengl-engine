// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  27/11/2023

#include <cmath>
#include <stdexcept>
#include "cubic_bezier.h"

CubicBezier::CubicBezier(std::unique_ptr<DrawableObject> object,
                         glm::mat4x3 control_points,
                         float speed,
                         AnimationArgs args) :
        object(std::move(object)), control_points(control_points), speed(speed), args(args), t(0.0f) { }

void CubicBezier::translate() {
    glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
    glm::vec3 p = parameters * bezier_coefficients * glm::transpose(control_points);
    this->object->setTranslate(p);
}

void CubicBezier::step(float delta_time) {
    t += delta_time * speed;
    if (args & CYCLE) {
        if ((speed < 0 && t < 0.0f) || (speed > 0 && t > 1.0f))
            speed = -speed;
    } else if (args & RESTART) {
        if (t > 1.0f)
            t = 0.0f;
        else if (t < 0.0f)
            t = 1.0f;
    } else
        throw std::runtime_error("CubicBezier::step: Invalid CubicAnimationArgs");

    translate();
}

void CubicBezier::draw() {
    this->object->draw();
}
