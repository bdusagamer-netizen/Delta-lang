#include "parser.hpp"

namespace delta {

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens) {}

bool Parser::isAtEnd() const {
    return peek().type == TokenType::END_OF_FILE;
}

const Token& Parser::peek() const {
    return tokens[current];
}

const Token& Parser::previous() const {
    return tokens[current - 1];
}

const Token& Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

bool Parser::match(std::initializer_list<TokenType> types) {
    for (TokenType t : types) {
        if (check(t)) {
            advance();
            return true;
        }
    }
    return false;
}

// -------------------------------
// Program = single expression
// -------------------------------
std::vector<ExprPtr> Parser::parseProgram() {
    std::vector<ExprPtr> program;
    while (!isAtEnd()) {
        program.push_back(parse());
    }
    return program;
}

ExprPtr Parser::parse() {
    return expression();
}

// -------------------------------
// Expression grammar
// -------------------------------

ExprPtr Parser::expression() {
    return assignment();
}

ExprPtr Parser::assignment() {
    ExprPtr expr = equality();
    return expr;
}

ExprPtr Parser::equality() {
    ExprPtr expr = comparison();

    while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        std::string op = previous().lexeme;
        ExprPtr right = comparison();
        expr = std::make_shared<BinaryExpr>(op, expr, right);
    }

    return expr;
}

ExprPtr Parser::comparison() {
    ExprPtr expr = term();

    while (match({TokenType::GREATER, TokenType::GREATER_EQUAL,
                  TokenType::LESS, TokenType::LESS_EQUAL})) {
        std::string op = previous().lexeme;
        ExprPtr right = term();
        expr = std::make_shared<BinaryExpr>(op, expr, right);
    }

    return expr;
}

ExprPtr Parser::term() {
    ExprPtr expr = factor();

    while (match({TokenType::PLUS, TokenType::MINUS})) {
        std::string op = previous().lexeme;
        ExprPtr right = factor();
        expr = std::make_shared<BinaryExpr>(op, expr, right);
    }

    return expr;
}

ExprPtr Parser::factor() {
    ExprPtr expr = unary();

    while (match({TokenType::STAR, TokenType::SLASH})) {
        std::string op = previous().lexeme;
        ExprPtr right = unary();
        expr = std::make_shared<BinaryExpr>(op, expr, right);
    }

    return expr;
}

ExprPtr Parser::unary() {
    if (match({TokenType::MINUS})) {
        std::string op = previous().lexeme;
        ExprPtr right = unary();
        return std::make_shared<BinaryExpr>(op, std::make_shared<NumberExpr>(0), right);
    }
    return dereference();
}

ExprPtr Parser::dereference() {
    ExprPtr expr = primary();

    while (match({TokenType::LEFT_PAREN})) {
        expr = objectCall(expr);
    }

    return expr;
}

ExprPtr Parser::primary() {
    if (match({TokenType::NUMBER})) {
        double value = std::stod(previous().lexeme);
        return std::make_shared<NumberExpr>(value);
    }

    if (match({TokenType::IDENTIFIER})) {
        return std::make_shared<VarExpr>(previous().lexeme);
    }

    if (match({TokenType::LEFT_PAREN})) {
        ExprPtr expr = expression();
        match({TokenType::RIGHT_PAREN});
        return expr;
    }

    return std::make_shared<NumberExpr>(0);
}

ExprPtr Parser::objectCall(ExprPtr callee) {
    std::vector<ExprPtr> args;

    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            args.push_back(expression());
        } while (match({TokenType::COMMA}));
    }

    match({TokenType::RIGHT_PAREN});
    return std::make_shared<CallExpr>(callee, args);
}

} // namespace delta