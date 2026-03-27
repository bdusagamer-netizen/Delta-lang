#include "compiler.hpp"
#include "../runtime/environment.hpp"
#include "../ast/ast.hpp"

namespace delta {

Compiler::Compiler(Environment& e)
    : env(e) {}

double Compiler::compile(const ExprPtr& program) {
    return env.evaluate(program);
}

} // namespace delta