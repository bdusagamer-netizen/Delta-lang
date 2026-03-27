#pragma once

#include "ast_nodes.hpp"
#include <string>

namespace delta {

class NumberExpr : public Expr {
public:
    double value;

    explicit NumberExpr(double v) : value(v) {}

    std::string toString() const override {
        return std::to_string(value);
    }

    double evaluate() const override {
        return value;
    }
};

} // namespace delta