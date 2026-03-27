#include "lexer.hpp"
#include <cctype>

namespace delta {

Lexer::Lexer(const std::string& src)
    : source(src) {}

bool Lexer::isAtEnd() const {
    return current >= source.size();
}

char Lexer::advance() {
    return source[current++];
}

char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return source[current];
}

char Lexer::peekNext() const {
    if (current + 1 >= source.size()) return '\0';
    return source[current + 1];
}

bool Lexer::match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;
    current++;
    return true;
}

void Lexer::addToken(TokenType type) {
    std::string text = source.substr(start, current - start);
    tokens.push_back({type, text, line});
}

void Lexer::number() {
    while (std::isdigit(peek())) advance();

    if (peek() == '.' && std::isdigit(peekNext())) {
        advance(); // consume '.'
        while (std::isdigit(peek())) advance();
    }

    addToken(TokenType::NUMBER);
}

void Lexer::identifier() {
    while (std::isalnum(peek()) || peek() == '_') advance();
    addToken(TokenType::IDENTIFIER);
}

void Lexer::scanToken() {
    char c = advance();

    switch (c) {
        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;
        case ',':
            addToken(TokenType::COMMA);
            break;
        case '+':
            addToken(TokenType::PLUS);
            break;
        case '-':
            addToken(TokenType::MINUS);
            break;
        case '*':
            addToken(TokenType::STAR);
            break;
        case '/':
            addToken(TokenType::SLASH);
            break;

        // Comparisons
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;

        // Equality
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::IDENTIFIER);
            break;
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::IDENTIFIER);
            break;

        // Whitespace
        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            line++;
            break;

        default:
            if (std::isdigit(c)) {
                number();
            } else if (std::isalpha(c) || c == '_') {
                identifier();
            }
            break;
    }
}

std::vector<Token> Lexer::tokenize() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.push_back({TokenType::END_OF_FILE, "", line});
    return tokens;
}

} // namespace delta