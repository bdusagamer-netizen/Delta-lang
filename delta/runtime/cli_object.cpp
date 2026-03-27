#include "cli_object.hpp"
#include "../ast/string_expr.hpp"

namespace delta {

CLIObject::CLIObject(Environment& e)
    : env(e) {}

void CLIObject::printSymbolic(const ExprPtr& expr) {
    if (!expr) {
        std::cout << "null\n";
        return;
    }
    std::cout << expr->toString() << "\n";
}

void CLIObject::printEvaluated(const ExprPtr& expr) {
    if (!expr) {
        std::cout << "null\n";
        return;
    }
    // This assumes env.evaluate(expr) uses MathObject internally
    double value = env.evaluate(expr);
    std::cout << value << "\n";
}

void CLIObject::printEvaluatedValue(double value) {
    std::cout << value << "\n";
}

void CLIObject::inputToVar(const std::string& name) {
    std::string input;
    std::getline(std::cin, input);
    env.set(name, std::make_shared<StringExpr>(input));
}

void CLIObject::inputToVarWithEvent(const std::string& name, const std::string& eventId) {
    std::string input;
    std::getline(std::cin, input);
    env.set(name, std::make_shared<StringExpr>(input));
    // event dispatch will be added later
}

} // namespace delta