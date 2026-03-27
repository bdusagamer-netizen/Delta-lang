#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

namespace delta {

class EventBus {
public:
    using Callback = std::function<void()>;

    void subscribe(const std::string& eventName, Callback cb);
    void fire(const std::string& eventName);

private:
    std::unordered_map<std::string, std::vector<Callback>> listeners;
};

} // namespace delta