#pragma once

#include <string>
#include <vector>
#include <memory>

namespace delta {

// Forward declarations
class Expr;
class NumberExpr;
class VarExpr;
class BinaryExpr;
class CallExpr;
class StringExpr;
class Statement;

// Shared pointer alias
using ExprPtr = std::shared_ptr<Expr>;
using StmtPtr = std::shared_ptr<Statement>;

// === Base Expression ===
class Expr {
public:
    virtual ~Expr() = default;
};

// === Number Expression ===
class NumberExpr : public Expr {
public:
    double value;
    explicit NumberExpr(double value) : value(value) {}
};

// === Variable Expression ===
class VarExpr : public Expr {
public:
    std::string name;
    explicit VarExpr(const std::string& name) : name(name) {}
};

// === Binary Expression ===
class BinaryExpr : public Expr {
public:
    std::string op;
    ExprPtr left;
    ExprPtr right;
    BinaryExpr(const std::string& op, ExprPtr left, ExprPtr right)
        : op(op), left(left), right(right) {}
};

// === Call Expression ===
class CallExpr : public Expr {
public:
    std::string callee;
    std::vector<ExprPtr> args;
    CallExpr(const std::string& callee, const std::vector<ExprPtr>& args)
        : callee(callee), args(args) {}
};

// === String Expression ===
class StringExpr : public Expr {
public:
    std::string value;
    explicit StringExpr(const std::string& value) : value(value) {}
};

// === Statement Base ===
class Statement {
public:
    virtual ~Statement() = default;
};

// You can add specific statement types here (e.g., PrintStmt, AssignStmt)

} // namespace delta