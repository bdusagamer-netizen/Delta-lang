#pragma once

#include "./ast/ast.hpp"
#include "environment.hpp"

namespace delta {

class MathObject {
public:
    explicit MathObject(Environment& env);
    double evaluate(const ExprPtr& expr);

private:
    Environment& env;

    double evalNumber(const NumberExpr* num);
    double evalVar(const VarExpr* var);
    double evalBinary(const BinaryExpr* bin);

    // New math functions
    double evalRandom();
    double evalSqrt(const ExprPtr& arg);
    double evalCbrt(const ExprPtr& arg);
    double evalNthrt(const ExprPtr& base, const ExprPtr& n);
    double evalFrthrt(const ExprPtr& arg); // Assuming frthrt = fourth root
};

} // namespace delta