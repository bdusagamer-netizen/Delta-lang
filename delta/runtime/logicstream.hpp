#pragma once

#include <string>
#include <vector>
#include <functional>
#include "../ast/ast.hpp"
#include "environment.hpp"
#include "event_bus.hpp"

namespace delta {

struct LogicstreamRule {
    std::string eventName;
    ExprPtr condition;     // if (~<answer> == ~<sum>)
    ExprPtr body;          // the block to execute
};

class LogicstreamEngine {
public:
    LogicstreamEngine(Environment& env, EventBus& bus);

    // Add a rule parsed from logicstream(...)
    void addRule(const LogicstreamRule& rule);

    // Called by EventBus when an event fires
    void onEvent(const std::string& eventName);

private:
    Environment& env;
    EventBus& bus;
    std::vector<LogicstreamRule> rules;
};

} // namespace delta