#pragma once

#include "../ast/ast.hpp"
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
};

} // namespace delta