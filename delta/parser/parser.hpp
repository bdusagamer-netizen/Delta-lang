#pragma once

#include <vector>
#include <memory>
#include "../lexer/lexer.hpp"
#include "../ast/ast.hpp"

namespace delta {

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    // Parse a full program (sequence of expressions)
    std::vector<ExprPtr> parseProgram();

    // Parse a single expression
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

    // Expression grammar
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
};

} // namespace delta