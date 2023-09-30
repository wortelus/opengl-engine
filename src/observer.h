//
// Created by wortelus on 30.9.23.
//

#ifndef ZPG_OBSERVER_H
#define ZPG_OBSERVER_H

#include <string>

enum class EventType {
    LoadShader,
};

struct EventInfo {
    std::string target_shader_name;
    EventType type;
};

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const EventInfo& eventInfo) = 0;
};

class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify() = 0;
};




#endif //ZPG_OBSERVER_H
