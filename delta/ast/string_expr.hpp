#pragma once

#include "ast.hpp"
#include <string>

namespace delta {

class StringExpr : public Expr {
public:
    std::string value;

    explicit StringExpr(const std::string& v)
        : value(v) {}

    std::string toString() const override {
        return "\"" + value + "\"";
    }
};

} // namespace delta