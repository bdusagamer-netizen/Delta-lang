#pragma once

#include <string>
#include <iostream>
#include "../ast/ast.hpp"
#include "environment.hpp"

namespace delta {

class CLIObject {
public:
    explicit CLIObject(Environment& env);

    // Symbolic print
    void printSymbolic(const ExprPtr& expr);

    // Evaluated print (AST → math engine)
    void printEvaluated(const ExprPtr& expr);

    // Evaluated numeric print (double)
    void printEvaluatedValue(double value);   // ← REQUIRED

    // Input operations
    void inputToVar(const std::string& name);
    void inputToVarWithEvent(const std::string& name, const std::string& eventId);

private:
    Environment& env;
};

} // namespace delta