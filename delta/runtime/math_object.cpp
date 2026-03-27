#include "math_object.hpp"
#include <cmath>
#include <cstdlib>
#include <stdexcept>

namespace delta {

MathObject::MathObject(Environment& env) : env(env) {}

double MathObject::evaluate(const ExprPtr& expr) {
    // Dispatch logic here (not shown)
    return 0.0;
}

double MathObject::evalNumber(const NumberExpr* num) {
    return num->value;
}

return env.get(var->name);
double MathObject::evalBinary(const BinaryExpr* bin) {
    // Binary operation logic (not shown)
    return 0.0;
}

// New math functions

double MathObject::evalRandom() {
    return static_cast<double>(rand()) / RAND_MAX;
}

double MathObject::evalSqrt(const ExprPtr& arg) {
    double val = evaluate(arg);  // ✅ Evaluate before using
    if (val < 0) throw std::domain_error("sqrt: negative input");
    return std::sqrt(val);
}

double MathObject::evalCbrt(const ExprPtr& arg) {
    return std::cbrt(evaluate(arg));  // ✅ Evaluate before using
}

double MathObject::evalNthrt(const ExprPtr& base, const ExprPtr& n) {
    double b = evaluate(base);  // ✅ Evaluate both
    double r = evaluate(n);
    if (r == 0) throw std::domain_error("nthrt: zero root");
    return std::pow(b, 1.0 / r);
}

double MathObject::evalFrthrt(const ExprPtr& arg) {
    return std::pow(evaluate(arg), 0.25);  // ✅ Evaluate before using
}

} // namespace delta