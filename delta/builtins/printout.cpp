#include "printout.hpp"
#include <iostream>
#include "../runtime/environment.hpp"   // ← add this include

namespace delta {

void Printout::printSymbolic(const ExprPtr& expr) {
    if (!expr) {
        std::cout << "null\n";
        return;
    }
    std::cout << expr->toString() << "\n";
}

void Printout::printEvaluated(const ExprPtr& expr, Environment& env) {
    if (!expr) {
        std::cout << "null\n";
        return;
    }
    double value = env.evaluate(expr);
    std::cout << value << "\n";
}

} // namespace delta