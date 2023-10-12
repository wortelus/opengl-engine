// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  30/9/2023

#ifndef ZPG_OBSERVER_H
#define ZPG_OBSERVER_H

#include <string>
#include "event_args.h"

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const EventArgs& event_args) = 0;
};

class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify() = 0;
};




#endif //ZPG_OBSERVER_H
