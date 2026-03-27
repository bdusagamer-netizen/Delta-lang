#pragma once
#include "../ast/ast.hpp"

namespace delta {

class Environment;

class Compiler {
public:
    Compiler(Environment& e);
    double compile(const ExprPtr& program);

private:
    Environment& env;
};

} // namespace delta