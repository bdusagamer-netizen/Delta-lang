#pragma once
#include "../ast/ast.hpp"

namespace delta {

class Environment {
public:
    double evaluate(const ExprPtr& expr) const;
};

} // namespace delta