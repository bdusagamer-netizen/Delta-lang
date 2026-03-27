#pragma once

#include "ast_nodes.hpp"
#include <memory>
#include <stdexcept>
#include <string>

namespace delta {

class BinaryExpr : public Expr {
public:
    std::string op;
    std::shared_ptr<Expr> left;
    std::shared_ptr<Expr> right;

    BinaryExpr(const std::string& oper,
               std::shared_ptr<Expr> l,
               std::shared_ptr<Expr> r)
        : op(oper), left(std::move(l)), right(std::move(r)) {}

    std::string toString() const override {
        return left->toString() + " " + op + " " + right->toString();
    }

    double evaluate() const override {
        double L = left->evaluate();
        double R = right->evaluate();

        if (op == "+") return L + R;
        if (op == "-") return L - R;
        if (op == "*") return L * R;
        if (op == "/") return R == 0.0 ? 0.0 : L / R;

        throw std::runtime_error("Unknown operator in BinaryExpr: " + op);
    }
};

} // namespace delta