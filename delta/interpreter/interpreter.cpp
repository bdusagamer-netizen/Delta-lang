#include <memory>
#include <string>

#include "interpreter.hpp"
#include "../ast/ast.hpp"              // Expr, ExprPtr, CallExpr, VarExpr
#include "../runtime/value.hpp"                 // Value
#include "../runtime/environment.hpp"
#include "../runtime/cli_object.hpp"
#include "../runtime/math_object.hpp"

namespace delta {

Interpreter::Interpreter(Environment& e, CLIObject& c, MathObject& m)
    : env(e), cli(c), math(m) {}

void Interpreter::execute(const ExprPtr& expr) {
    if (!expr) return;

    if (auto call = dynamic_cast<CallExpr*>(expr.get())) {
        evalCall(call);
        return;
    }

    cli.printSymbolic(expr);
}

void Interpreter::evalCall(const CallExpr* call) {
    auto calleeVar = dynamic_cast<VarExpr*>(call->callee.get());
    if (!calleeVar) {
        cli.printSymbolic(std::make_shared<CallExpr>(*call));
        return;
    }

    const std::string& name = calleeVar->name;

    if (name == "cli-printout<=") {
        cli.printSymbolic(call->args[0]);
        return;
    }

    if (name == "cli-printout=>") {
        Value result = env.evaluate(call->args[0]);   // your evaluator
        double value = result.asNumber();
        cli.printEvaluatedValue(value);
        return;
    }

    cli.printSymbolic(std::make_shared<CallExpr>(*call));
}

} // namespace delta