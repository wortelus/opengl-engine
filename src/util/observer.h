// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  30/9/2023

#ifndef ZPG_OBSERVER_H
#define ZPG_OBSERVER_H

#include <string>
#include <vector>
#include "event_args.h"

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const EventArgs& event_args) = 0;
};

class ISubject {
    std::vector<IObserver*> observers = {};
public:
    void attach(IObserver* observer);
    void detach(IObserver* observer);
    void notify(const EventArgs& event_args);
};

class ISubjectSingle {
    IObserver* observer = nullptr;
public:
    void attach(IObserver* new_observer);
    void detach();
    void notify(const EventArgs& event_args);
};


#endif //ZPG_OBSERVER_H
