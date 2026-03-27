// delta/ast/call_expr.hpp
#pragma once

#include "ast_nodes.hpp"
#include <vector>
#include <memory>
#include <stdexcept>   // ← add this

namespace delta {

class CallExpr : public Expr {
public:
    std::shared_ptr<Expr> callee;
    std::vector<std::shared_ptr<Expr>> args;

    CallExpr(std::shared_ptr<Expr> c, std::vector<std::shared_ptr<Expr>> a)
        : callee(std::move(c)), args(std::move(a)) {}

    std::string toString() const override {
        std::string s = callee->toString() + "(";
        for (size_t i = 0; i < args.size(); ++i) {
            s += args[i]->toString();
            if (i + 1 < args.size()) s += ", ";
        }
        s += ")";
        return s;
    }

    double evaluate() const override {
        throw std::runtime_error("CallExpr::evaluate() must be handled by interpreter");
    }
};

} // namespace delta