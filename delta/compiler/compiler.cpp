#include "compiler.hpp"
#include "../ast/ast.hpp"
#include "../runtime/environment.hpp"
#include "../runtime/math_object.hpp"

namespace delta {

Compiler::Compiler(Environment& env)
    : env(env), math(env) {}

double Compiler::compile(const ExprPtr& program) {
    // For now, compilation = evaluation
    return math.evaluate(program);
}

} // namespace delta