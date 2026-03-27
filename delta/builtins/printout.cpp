#include "printout.hpp"
#include "../runtime/cli_object.hpp"
#include <iostream>

namespace delta {

void Printout::printSymbolic(const ExprPtr& expr) {
    CLIObject cli;
    cli.printSymbolic(expr);
}

void Printout::printEvaluated(double value) {
    std::cout << value << "\n";
}

} // namespace delta