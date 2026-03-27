#pragma once

#include <string>
#include <memory>
#include "../ast/ast.hpp"

namespace delta {

class Environment; // forward declaration

class Printout {
public:
    static void printSymbolic(const ExprPtr& expr);
    static void printEvaluated(const ExprPtr& expr, Environment& env);
};

} // namespace delta