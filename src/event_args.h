//
// Created by wortelus on 5.10.23.
//

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
