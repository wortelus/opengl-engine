// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  2/12/2023

#include <stdexcept>
#include "cubic_chain.h"
#include "cubic_bezier.h"

CubicChain::CubicChain(std::unique_ptr<DrawableObject> object, const glm::vec3 initial_position, float speed,
                       AnimationArgs args)
        : object(std::move(object)), speed(speed), args(args), t(0.0f) {
    if (args & CYCLE)
        throw std::runtime_error("CubicChain::CubicChain: CYCLE is not supported");

    control_points.push_back(initial_position);
}

void CubicChain::translate() {
    if (control_points.size() < 4) {
        this->object->setTranslate(control_points[0]);
        return;
    }

    int offset = current_control_point * 3;
    glm::mat4x3 points = glm::mat4x3(control_points[offset], control_points[offset + 1],
                                     control_points[offset + 2], control_points[offset + 3]);

    glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
    glm::vec3 p = parameters * CubicBezier::bezier_coefficients * glm::transpose(points);
    this->object->setTranslate(p);
}

void CubicChain::addControlPoint(glm::mat3x3 control_point) {
    control_points.push_back(control_point[0]);
    control_points.push_back(control_point[1]);
    control_points.push_back(control_point[2]);
}

void CubicChain::step(float delta_time) {
    int max_offset = static_cast<int>((control_points.size() - 1) / 3) - 1;
    t += delta_time * speed;
    if (args & RESTART) {
        if (t > 1.0f) {
            t = 0.0f;
            current_control_point++;
            if (current_control_point > max_offset)
                current_control_point = 0;
        } else if (t < 0.0f) {
            t = 1.0f;
            current_control_point--;
            if (current_control_point < 0)
                current_control_point = max_offset;
        }
    } else
        throw std::runtime_error("CubicChain::step: Invalid CubicAnimationArgs");

    translate();
}

void CubicChain::draw() {
    this->object->draw();
}


