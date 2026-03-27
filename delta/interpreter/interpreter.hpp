 #pragma once

#include <memory>
#include "../runtime/value.hpp"
#include "../runtime/environment.hpp"
#include "../runtime/cli_object.hpp"
#include "../runtime/math_object.hpp"
#include "../ast/ast.hpp"   // where Expr, CallExpr, VarExpr, ExprPtr live

namespace delta {

class Interpreter {
public:
    Interpreter(Environment& e, CLIObject& c, MathObject& m);

    void execute(const ExprPtr& expr);

private:
    Environment& env;
    CLIObject& cli;
    MathObject& math;

    void evalCall(const CallExpr* call);
};

} // namespace delta