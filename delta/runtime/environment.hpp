#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "../ast/ast.hpp"

namespace delta {

class Environment {
public:
    Environment() = default;

    // Store a symbolic AST under a variable name
    void set(const std::string& name, ExprPtr expr);

    // Retrieve the symbolic AST for a variable
    ExprPtr get(const std::string& name) const;

    // Evaluate an expression using this environment
    double evaluate(const ExprPtr& expr) const;

    // Check if a variable exists
    bool exists(const std::string& name) const;

private:
    std::unordered_map<std::string, ExprPtr> values;
};

} // namespace delta