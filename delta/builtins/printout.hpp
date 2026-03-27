#pragma once
#include "../ast/ast.hpp"

namespace delta {

class Printout {
public:
    static void printSymbolic(const ExprPtr& expr);
    static void printEvaluated(double value);
};

} // namespace delta