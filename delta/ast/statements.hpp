#pragma once

#include <memory>
#include <vector>
#include <string>
#include "ast.hpp"
#include "../runtime/logicstream.hpp"

namespace delta {

class Stmt {
public:
    virtual ~Stmt() = default;
};

using StmtPtr = std::shared_ptr<Stmt>;

class ExprStmt : public Stmt {
public:
    ExprPtr expr;
    explicit ExprStmt(ExprPtr e) : expr(std::move(e)) {}
};

class VarStmt : public Stmt {
public:
    std::string name;
    ExprPtr initializer;
    VarStmt(std::string n, ExprPtr init)
        : name(std::move(n)), initializer(std::move(init)) {}
};

class BlockStmt : public Stmt {
public:
    std::vector<StmtPtr> statements;
    explicit BlockStmt(std::vector<StmtPtr> stmts)
        : statements(std::move(stmts)) {}
};

class LogicstreamStmt : public Stmt {
public:
    std::vector<LogicstreamRule> rules;
    explicit LogicstreamStmt(std::vector<LogicstreamRule> r)
        : rules(std::move(r)) {}
};

} // namespace delta