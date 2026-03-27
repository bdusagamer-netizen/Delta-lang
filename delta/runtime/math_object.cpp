#include "math_object.hpp"
#include <stdexcept>

namespace delta {

MathObject::MathObject(Environment& e)
    : env(e) {}

double MathObject::evaluate(const ExprPtr& expr) {
    if (!expr) throw std::runtime_error("Null expression");

    if (auto num = dynamic_cast<NumberExpr*>(expr.get()))
        return evalNumber(num);

    if (auto var = dynamic_cast<VarExpr*>(expr.get()))
        return evalVar(var);

    if (auto bin = dynamic_cast<BinaryExpr*>(expr.get()))
        return evalBinary(bin);

    throw std::runtime_error("Unsupported expression type for math evaluation");
}

double MathObject::evalNumber(const NumberExpr* num) {
    return num->value;
}

double MathObject::evalVar(const VarExpr* var) {
    ExprPtr stored = env.get(var->name);
    return evaluate(stored);
}

double MathObject::evalBinary(const BinaryExpr* bin) {
    double left = evaluate(bin->left);
    double right = evaluate(bin->right);

    if (bin->op == "+") return left + right;
    if (bin->op == "-") return left - right;
    if (bin->op == "*") return left * right;
    if (bin->op == "/") return left / right;
    if (bin->op == "^") return std::pow(left, right);

    throw std::runtime_error("Unknown math operator: " + bin->op);
}

} // namespace delta