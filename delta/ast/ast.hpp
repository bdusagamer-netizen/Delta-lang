#pragma once

#include "ast_nodes.hpp"
#include "number_expr.hpp"
#include "var_expr.hpp"
#include "binary_expr.hpp"
#include "call_expr.hpp"

#include <memory>

namespace delta {

using ExprPtr = std::shared_ptr<Expr>;

} // namespace delta