// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  5/10/2023

#ifndef ZPG_EVENT_ARGS_H
#define ZPG_EVENT_ARGS_H


#include "glm/vec3.hpp"

enum class EventType {
    UNKNOWN,

    U_TRANSLATION,
    S_TRANSLATION,

    U_ROTATION,
    S_ROTATION,

    S_ROTATION_POINT_AXIS,
    U_ROTATION_POINT_ANGLE,
    S_ROTATION_POINT_ANGLE,
    S_ROTATION_POINT_ORIGIN,

    U_SCALE,
    S_SCALE,

    U_MODEL_MATRIX,
    U_VIEW_MATRIX,
    U_PROJECTION_MATRIX,
    U_NORMAL_MATRIX,

    U_CAMERA_POSITION,

    U_MATERIAL,

    U_LIGHT_SINGLE,
    U_LIGHTS,

    //
    // general uniforms
    //

    U_1I,
    U_1F,
    U_3FV,
    U_4FV,
    U_MAT_3FV,
    U_MAT_4FV,
};

struct EventArgs {
    EventArgs(const char* name, EventType eventType)
            : name(name), type(eventType) {}

    EventArgs(EventType eventType) : type(eventType) {}

    virtual ~EventArgs() = default;  // necessary for dynamic casting
    const char* name = nullptr;
    EventType type = EventType::UNKNOWN;
};

template<typename T>
struct EventPayload : public EventArgs {
    EventPayload(const T& payloadValue, EventType eventType)
            : EventArgs(eventType), payload(payloadValue) {}

    EventPayload(const char* name, const T& payloadValue, EventType eventType)
            : EventArgs(name, eventType), payload(payloadValue) {}

    T payload;

    T getPayload() const {
        return payload;
    }
};

#endif //ZPG_EVENT_ARGS_H
