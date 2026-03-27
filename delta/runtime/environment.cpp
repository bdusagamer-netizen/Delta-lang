#include "environment.hpp"
#include "../ast/ast.hpp"

namespace delta {

double Environment::evaluate(const ExprPtr& expr) const {
    if (!expr) return 0.0;

    if (auto num = dynamic_cast<NumberExpr*>(expr.get())) {
        return num->value;
    }

    if (auto bin = dynamic_cast<BinaryExpr*>(expr.get())) {
        double left = evaluate(bin->left);
        double right = evaluate(bin->right);

        if (bin->op == "+") return left + right;
        if (bin->op == "-") return left - right;
        if (bin->op == "*") return left * right;
        if (bin->op == "/") return right != 0 ? left / right : 0.0;

        return 0.0;
    }

    // VarExpr / CallExpr can be extended later
    return 0.0;
}

} // namespace delta