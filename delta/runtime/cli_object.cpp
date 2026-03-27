#include "cli_object.hpp"
#include <iostream>

namespace delta {

void CLIObject::printSymbolic(const ExprPtr& expr) {
    printExpr(expr);
    std::cout << "\n";
}

void CLIObject::printEvaluatedValue(double value) {
    std::cout << value << "\n";
}

void CLIObject::printExpr(const ExprPtr& expr) {
    if (!expr) {
        std::cout << "nil";
        return;
    }

    // Number literal
    if (auto num = dynamic_cast<NumberExpr*>(expr.get())) {
        std::cout << num->value;
        return;
    }

    // Variable
    if (auto var = dynamic_cast<VarExpr*>(expr.get())) {
        std::cout << var->name;
        return;
    }

    // Function/object call
    if (auto call = dynamic_cast<CallExpr*>(expr.get())) {
        std::cout << "(";
        printExpr(call->callee);

        for (size_t i = 0; i < call->args.size(); ++i) {
            std::cout << " ";
            printExpr(call->args[i]);
        }

        std::cout << ")";
        return;
    }

    // Fallback for unknown nodes
    std::cout << "<expr>";
}

} // namespace delta