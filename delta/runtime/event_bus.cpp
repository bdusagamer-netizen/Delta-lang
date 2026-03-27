#include "event_bus.hpp"

namespace delta {

void EventBus::subscribe(const std::string& eventName, Callback cb) {
    listeners[eventName].push_back(cb);
}

void EventBus::fire(const std::string& eventName) {
    if (listeners.count(eventName) == 0)
        return;

    for (auto& cb : listeners[eventName]) {
        cb();
    }
}

} // namespace delta