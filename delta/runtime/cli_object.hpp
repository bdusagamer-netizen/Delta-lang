#pragma once
#include "../ast/ast.hpp"

namespace delta {

class CLIObject {
public:
    void printSymbolic(const ExprPtr& expr);
    void printEvaluatedValue(double value);

private:
    void printExpr(const ExprPtr& expr);
};

} // namespace delta