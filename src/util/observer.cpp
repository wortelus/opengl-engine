// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  30/9/2023

#include "observer.h"
#include <algorithm>

void ISubject::notify(const EventArgs &event_args) {
    for (auto observer: this->observers) {
        observer->update(event_args);
    }
}

void ISubject::attach(IObserver *observer) {
    this->observers.push_back(observer);
}

void ISubject::detach(IObserver *observer) {
    this->observers.erase(std::remove(this->observers.begin(), this->observers.end(), observer),
                          this->observers.end());
}

void ISubjectSingle::attach(IObserver *new_observer) {
    this->observer = new_observer;
}

void ISubjectSingle::notify(const EventArgs &event_args) {
    if (this->observer != nullptr) this->observer->update(event_args);
}

void ISubjectSingle::detach() {
    this->observer = nullptr;
}
