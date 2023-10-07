// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  5/10/2023

#ifndef ZPG_EVENT_ARGS_H
#define ZPG_EVENT_ARGS_H


#include "glm/vec3.hpp"

enum class EventType {
    U_TRANSLATION,
    S_TRANSLATION,
    U_ROTATION,
    S_ROTATION,
    U_SCALE,
    S_SCALE
};

struct EventArgs {
    glm::vec3 payload;
    EventType type;
};


#endif //ZPG_EVENT_ARGS_H
