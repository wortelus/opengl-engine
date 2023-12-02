// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  1/12/2023

#include <stdexcept>
#include "linear.h"

Linear::Linear(std::unique_ptr<DrawableObject> object, glm::vec3 a, glm::vec3 u, float max_distance, float speed, AnimationArgs args)
        : object(std::move(object)), a(a), u(glm::normalize(u)), max_distance(max_distance), speed(speed), args(args) {
    if (glm::length(u) == 0.0f)
        throw std::runtime_error("Linear::Linear: Invalid direction vector");
}

void Linear::translate() {
    this->object->setTranslate(a + t * u);
}

void Linear::step(float delta_time) {
    t += delta_time * speed;
    if (args & CYCLE) {
        if ((speed < 0 && t < 0.0f) || (speed > 0 && t > max_distance))
            speed = -speed;
    } else if (args & RESTART) {
        if (t > max_distance)
            t = 0.0f;
        else if (t < 0.0f)
            t = max_distance;
    } else
        throw std::runtime_error("Linear::step: Invalid LinearAnimationArgs");

    translate();
}

void Linear::draw() {
    this->object->draw();
}
