#pragma once

#include "ast_nodes.hpp"
#include <string>
#include <stdexcept>

namespace delta {

class VarExpr : public Expr {
public:
    std::string name;

    explicit VarExpr(const std::string& n) : name(n) {}

    std::string toString() const override {
        return name;
    }

    double evaluate() const override {
        // Actual value resolution happens in the interpreter using an environment.
        throw std::runtime_error("VarExpr::evaluate() requires environment lookup");
    }
};

} // namespace delta