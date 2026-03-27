#pragma once

#include <string>

namespace delta {

class Expr {
public:
    virtual ~Expr() = default;

    // Symbolic representation (for cli-printout<= and debugging)
    virtual std::string toString() const = 0;

    // Numeric evaluation (math engine walks these)
    // Var lookup and environment handling are done outside the AST.
    virtual double evaluate() const = 0;
};

} // namespace delta