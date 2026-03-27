#include "lexer.hpp"
#include <cctype>

namespace delta {

Lexer::Lexer(const std::string& src)
    : source(src) {}

std::vector<Token> Lexer::tokenize() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.push_back({TokenType::END_OF_FILE, "", line});
    return tokens;
}

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
    tokens.push_back({type, source.substr(start, current - start), line});
}

void Lexer::addToken(TokenType type, const std::string& text) {
    tokens.push_back({type, text, line});
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

        case '{':
            addToken(TokenType::LEFT_BRACE);
            break;

        case '}':
            addToken(TokenType::RIGHT_BRACE);
            break;

        case ',':
            addToken(TokenType::COMMA);
            break;

        case '.':
            addToken(TokenType::DOT);
            break;

        case ';':
            addToken(TokenType::SEMICOLON);
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

        case '~':
            addToken(TokenType::TILDE);
            break;

        case '=':
            if (match('=')) addToken(TokenType::EQUAL_EQUAL);
            else if (match('>')) addToken(TokenType::PRINT_EVAL);
            else addToken(TokenType::EQUAL);
            break;

        case '!':
            if (match('=')) addToken(TokenType::BANG_EQUAL);
            else addToken(TokenType::BANG);
            break;

        case '<':
            if (match('=')) addToken(TokenType::LESS_EQUAL);
            else addToken(TokenType::LEFT_ANGLE);
            break;

        case '>':
            if (match('=')) addToken(TokenType::GREATER_EQUAL);
            else addToken(TokenType::RIGHT_ANGLE);
            break;

        case '"':
            stringLiteral();
            break;

        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            line++;
            break;

        default:
            if (std::isdigit(c)) {
                numberLiteral();
            } else if (std::isalpha(c) || c == '_') {
                identifier();
            }
            break;
    }
}

void Lexer::stringLiteral() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    if (isAtEnd()) return;

    advance(); // closing quote

    std::string value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, value);
}

void Lexer::numberLiteral() {
    while (std::isdigit(peek())) advance();

    if (peek() == '.' && std::isdigit(peekNext())) {
        advance();
        while (std::isdigit(peek())) advance();
    }

    addToken(TokenType::NUMBER, source.substr(start, current - start));
}

void Lexer::identifier() {
    while (std::isalnum(peek()) || peek() == '_') advance();

    std::string text = source.substr(start, current - start);
    addToken(keywordType(text), text);
}

TokenType Lexer::keywordType(const std::string& text) {
    if (text == "var") return TokenType::VAR;
    if (text == "cli") return TokenType::CLI;
    if (text == "logicstream") return TokenType::LOGICSTREAM;
    if (text == "on") return TokenType::ON;
    if (text == "event") return TokenType::EVENT;
    if (text == "if") return TokenType::IF;
    if (text == "else") return TokenType::ELSE;
    if (text == "math") return TokenType::MATH;

    return TokenType::IDENTIFIER;
}

} // namespace delta