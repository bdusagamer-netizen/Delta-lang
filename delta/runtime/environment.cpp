#include "environment.hpp"
#include <stdexcept>

namespace delta {

void Environment::set(const std::string& name, ExprPtr expr) {
    values[name] = expr;
}

ExprPtr Environment::get(const std::string& name) const {
    auto it = values.find(name);
    if (it == values.end()) {
        throw std::runtime_error("Undefined variable: " + name);
    }
    return it->second;
}

bool Environment::exists(const std::string& name) const {
    return values.find(name) != values.end();
}

double Environment::evaluate(const ExprPtr& expr) const {
    if (!expr) {
        throw std::runtime_error("Attempted to evaluate null expression");
    }

    // If it's a VarExpr, resolve recursively
    if (auto var = dynamic_cast<VarExpr*>(expr.get())) {
        return evaluate(get(var->name));
    }

    // Otherwise, use the AST node's evaluate()
    return expr->evaluate();
}

} // namespace delta