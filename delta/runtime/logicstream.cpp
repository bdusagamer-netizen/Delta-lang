#include "logicstream.hpp"
#include "../builtins/printout.hpp"
#include <iostream>

namespace delta {

LogicstreamEngine::LogicstreamEngine(Environment& e, EventBus& b)
    : env(e), bus(b) {}

void LogicstreamEngine::addRule(const LogicstreamRule& rule) {
    rules.push_back(rule);

    // Subscribe to event
    bus.subscribe(rule.eventName, [this, rule]() {
        this->onEvent(rule.eventName);
    });
}

void LogicstreamEngine::onEvent(const std::string& eventName) {
    for (auto& rule : rules) {
        if (rule.eventName != eventName)
            continue;

        // Evaluate condition
        double cond = env.evaluate(rule.condition);

        if (cond != 0) {
            // Execute body symbolically for now
            Printout::printSymbolic(rule.body);
        }
    }
}

} // namespace delta