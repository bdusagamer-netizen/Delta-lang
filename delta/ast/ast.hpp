#pragma once
#include <memory>
#include <string>
#include <vector>

namespace delta {

// Forward declaration
struct Expr;
using ExprPtr = std::shared_ptr<Expr>;

// Base expression node
struct Expr {
    virtual ~Expr() = default;
};

// Number literal
struct NumberExpr : Expr {
    double value;

    NumberExpr(double v)
        : value(v) {}
};

// Variable reference
struct VarExpr : Expr {
    std::string name;

    VarExpr(const std::string& n)
        : name(n) {}
};

// Binary expression (a + b, a * b, etc.)
struct BinaryExpr : Expr {
    std::string op;
    ExprPtr left;
    ExprPtr right;

    BinaryExpr(const std::string& oper, ExprPtr l, ExprPtr r)
        : op(oper), left(l), right(r) {}
};

// Function / object call
struct CallExpr : Expr {
    ExprPtr callee;
    std::vector<ExprPtr> args;

    CallExpr(const ExprPtr& c, const std::vector<ExprPtr>& a)
        : callee(c), args(a) {}
};

} // namespace delta