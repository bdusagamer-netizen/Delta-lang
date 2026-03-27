#pragma once

#include "../ast/ast.hpp"
#include "../ast/call_expr.hpp"
#include "environment.hpp"
#include "cli_object.hpp"
#include "math_object.hpp"

namespace delta {

class Interpreter {
public:
    Interpreter(Environment& env, CLIObject& cli, MathObject& math);

    // Execute a single expression (minimal mode)
    void execute(const ExprPtr& expr);

private:
    Environment& env;
    CLIObject& cli;
    MathObject& math;

    void evalCall(const CallExpr* call);
};

} // namespace delta