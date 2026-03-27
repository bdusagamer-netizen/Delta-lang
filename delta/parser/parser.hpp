#pragma once

#include <vector>
#include <memory>
#include "../lexer/lexer.hpp"
#include "../ast/ast.hpp"
#include "../ast/statements.hpp"

namespace delta {

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    // Parse a full program
    std::vector<StmtPtr> parseProgram();

    // Parse a single expression (legacy)
    ExprPtr parse();

private:
    const std::vector<Token>& tokens;
    int current = 0;

    bool isAtEnd() const;
    const Token& peek() const;
    const Token& previous() const;
    const Token& advance();
    bool check(TokenType type) const;
    bool match(std::initializer_list<TokenType> types);

    // Statements
    StmtPtr declaration();
    StmtPtr varDeclaration();
    StmtPtr statement();
    StmtPtr blockStatement();
    StmtPtr logicstreamStatement();

    // Expressions
    ExprPtr expression();
    ExprPtr assignment();
    ExprPtr equality();
    ExprPtr comparison();
    ExprPtr term();
    ExprPtr factor();
    ExprPtr unary();
    ExprPtr dereference();
    ExprPtr primary();
    ExprPtr objectCall(ExprPtr callee);

    // Helpers for logicstream/event
    LogicstreamRule parseLogicstreamRule();
};

} // namespace delta