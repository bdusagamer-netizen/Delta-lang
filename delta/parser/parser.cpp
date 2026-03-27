#include "parser.hpp"
#include <stdexcept>

namespace delta {

Parser::Parser(const std::vector<Token>& t) : tokens(t) {}

bool Parser::isAtEnd() const { return peek().type == TokenType::END_OF_FILE; }
const Token& Parser::peek() const { return tokens[current]; }
const Token& Parser::previous() const { return tokens[current - 1]; }
const Token& Parser::advance() { if (!isAtEnd()) current++; return previous(); }
bool Parser::check(TokenType type) const { return !isAtEnd() && peek().type == type; }

bool Parser::match(std::initializer_list<TokenType> types) {
    for (auto t : types) {
        if (check(t)) { advance(); return true; }
    }
    return false;
}

// -------- program / statements --------

std::vector<StmtPtr> Parser::parseProgram() {
    std::vector<StmtPtr> stmts;
    while (!isAtEnd()) {
        stmts.push_back(declaration());
    }
    return stmts;
}

ExprPtr Parser::parse() {
    return expression();
}

StmtPtr Parser::declaration() {
    if (match({TokenType::VAR})) return varDeclaration();
    if (match({TokenType::LOGICSTREAM})) return logicstreamStatement();
    return statement();
}

StmtPtr Parser::varDeclaration() {
    if (!check(TokenType::IDENTIFIER))
        throw std::runtime_error("Expected identifier after 'var'");
    std::string name = advance().lexeme;

    if (!match({TokenType::EQUAL}))
        throw std::runtime_error("Expected '=' after var name");

    ExprPtr init = expression();

    if (!match({TokenType::SEMICOLON}))
        throw std::runtime_error("Expected ';' after var declaration");

    return std::make_shared<VarStmt>(name, init);
}

StmtPtr Parser::statement() {
    if (match({TokenType::LEFT_BRACE})) return blockStatement();
    // Fallback: expression statement
    ExprPtr expr = expression();
    if (match({TokenType::SEMICOLON})) {
        return std::make_shared<ExprStmt>(expr);
    }
    return std::make_shared<ExprStmt>(expr);
}

StmtPtr Parser::blockStatement() {
    std::vector<StmtPtr> stmts;
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        stmts.push_back(declaration());
    }
    if (!match({TokenType::RIGHT_BRACE}))
        throw std::runtime_error("Expected '}' after block");
    return std::make_shared<BlockStmt>(stmts);
}

// -------- logicstream / event syntax --------

StmtPtr Parser::logicstreamStatement() {
    if (!match({TokenType::LEFT_PAREN}))
        throw std::runtime_error("Expected '(' after 'logicstream'");

    std::vector<LogicstreamRule> rules;

    // logicstream(on(...){...} on(...){...})
    while (!check(TokenType::RIGHT_PAREN) && !isAtEnd()) {
        rules.push_back(parseLogicstreamRule());
        // optional separators like commas or semicolons could go here
    }

    if (!match({TokenType::RIGHT_PAREN}))
        throw std::runtime_error("Expected ')' after logicstream(...)");

    return std::make_shared<LogicstreamStmt>(rules);
}

LogicstreamRule Parser::parseLogicstreamRule() {
    // on (event ~<name>; if condition) { body } else { body }
    if (!match({TokenType::ON}))
        throw std::runtime_error("Expected 'on' in logicstream");

    if (!match({TokenType::LEFT_PAREN}))
        throw std::runtime_error("Expected '(' after 'on'");

    if (!match({TokenType::EVENT}))
        throw std::runtime_error("Expected 'event' after 'on('");

    // event ~<identifier>
    if (!match({TokenType::TILDE}))
        throw std::runtime_error("Expected '~' after 'event'");

    if (!match({TokenType::LEFT_ANGLE}))
        throw std::runtime_error("Expected '<' after '~' in event");

    if (!check(TokenType::IDENTIFIER))
        throw std::runtime_error("Expected identifier in event name");

    std::string eventName = advance().lexeme;

    if (!match({TokenType::RIGHT_ANGLE}))
        throw std::runtime_error("Expected '>' after event identifier");

    if (!match({TokenType::SEMICOLON}))
        throw std::runtime_error("Expected ';' after event name");

    // if condition
    if (!match({TokenType::IF}))
        throw std::runtime_error("Expected 'if' after event;");

    ExprPtr condition = expression();

    if (!match({TokenType::RIGHT_PAREN}))
        throw std::runtime_error("Expected ')' after condition in on(...)");

    // body { ... }
    if (!match({TokenType::LEFT_BRACE}))
        throw std::runtime_error("Expected '{' for logicstream body");

    // For now, parse body as a single expression statement block
    std::vector<StmtPtr> bodyStmts;
    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        bodyStmts.push_back(declaration());
    }

    if (!match({TokenType::RIGHT_BRACE}))
        throw std::runtime_error("Expected '}' after logicstream body");

    // For now, we collapse body into a single ExprPtr: first statement if ExprStmt
    ExprPtr bodyExpr = nullptr;
    if (!bodyStmts.empty()) {
        if (auto es = std::dynamic_pointer_cast<ExprStmt>(bodyStmts.front())) {
            bodyExpr = es->expr;
        }
    }

    LogicstreamRule rule;
    rule.eventName = eventName;
    rule.condition = condition;
    rule.body = bodyExpr;
    return rule;
}

// -------- expressions (unchanged except CallExpr) --------

ExprPtr Parser::expression() { return assignment(); }
ExprPtr Parser::assignment() { return equality(); }

ExprPtr Parser::equality() {
    ExprPtr expr = comparison();
    while (match({TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL})) {
        std::string op = previous().lexeme;
        ExprPtr right = comparison();
        expr = std::make_shared<BinaryExpr>(op, expr, right);
    }
    return expr;
}

ExprPtr Parser::comparison() {
    ExprPtr expr = term();
    while (match({TokenType::LESS_EQUAL, TokenType::GREATER_EQUAL})) {
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
    if (match({TokenType::TILDE})) return dereference();
    return primary();
}

ExprPtr Parser::dereference() {
    if (!match({TokenType::LEFT_ANGLE}))
        throw std::runtime_error("Expected '<' after '~'");
    if (!check(TokenType::IDENTIFIER))
        throw std::runtime_error("Expected identifier inside ~< >");
    std::string name = advance().lexeme;
    if (!match({TokenType::RIGHT_ANGLE}))
        throw std::runtime_error("Expected '>' after ~<identifier");
    return std::make_shared<VarExpr>(name);
}

ExprPtr Parser::primary() {
    if (match({TokenType::NUMBER})) {
        double value = std::stod(previous().lexeme);
        return std::make_shared<NumberExpr>(value);
    }

    if (match({TokenType::STRING})) {
        return std::make_shared<VarExpr>(previous().lexeme);
    }

    if (match({TokenType::IDENTIFIER})) {
        ExprPtr ident = std::make_shared<VarExpr>(previous().lexeme);
        if (match({TokenType::LEFT_PAREN})) {
            return objectCall(ident);
        }
        return ident;
    }

    if (match({TokenType::LEFT_PAREN})) {
        ExprPtr expr = expression();
        if (!match({TokenType::RIGHT_PAREN}))
            throw std::runtime_error("Expected ')' after expression");
        return expr;
    }

    throw std::runtime_error("Unexpected token: " + peek().lexeme);
}

ExprPtr Parser::objectCall(ExprPtr callee) {
    std::vector<ExprPtr> args;
    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            args.push_back(expression());
        } while (match({TokenType::COMMA}));
    }
    if (!match({TokenType::RIGHT_PAREN}))
        throw std::runtime_error("Expected ')' after arguments");
    return std::make_shared<CallExpr>(callee, args);
}

} // namespace delta