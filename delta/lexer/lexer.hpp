#pragma once

#include <string>
#include <vector>

namespace delta {

enum class TokenType {
    // Single characters
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE,
    LEFT_ANGLE, RIGHT_ANGLE,
    COMMA, DOT, SEMICOLON,
    PLUS, MINUS, STAR, SLASH,
    EQUAL, BANG,

    // Multi-character operators
    EQUAL_EQUAL,
    BANG_EQUAL,
    LESS_EQUAL,
    GREATER_EQUAL,
    PRINT_SYM,      // <=
    PRINT_EVAL,     // =>

    // Keywords
    VAR,
    CLI,
    LOGICSTREAM,
    ON,
    EVENT,
    IF,
    ELSE,
    MATH,

    // Special syntax
    TILDE,          // ~
    IDENTIFIER,
    NUMBER,
    STRING,

    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    std::string toString() const {
        return lexeme;
    }
};

class Lexer {
public:
    explicit Lexer(const std::string& src);

    std::vector<Token> tokenize();

private:
    std::string source;
    std::vector<Token> tokens;

    int start = 0;
    int current = 0;
    int line = 1;

    bool isAtEnd() const;
    char advance();
    char peek() const;
    char peekNext() const;
    bool match(char expected);

    void addToken(TokenType type);
    void addToken(TokenType type, const std::string& text);

    void scanToken();
    void stringLiteral();
    void numberLiteral();
    void identifier();

    TokenType keywordType(const std::string& text);
};

} // namespace delta