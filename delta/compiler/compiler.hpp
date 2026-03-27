#pragma once

#include "../ast/ast.hpp"
#include "../runtime/environment.hpp"
#include "../runtime/math_object.hpp"

namespace delta {

class Compiler {
public:
    explicit Compiler(Environment& env);

    // Compile (currently evaluate) the AST
    double compile(const ExprPtr& program);

private:
    Environment& env;
    MathObject math;
};

} // namespace delta