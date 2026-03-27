#pragma once
#include <string>
#include <vector>

namespace delta {

enum class TokenType {
    LEFT_PAREN, RIGHT_PAREN,
    COMMA,
    PLUS, MINUS, STAR, SLASH,

    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    EQUAL_EQUAL, BANG_EQUAL,

    IDENTIFIER,
    NUMBER,

    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};

class Lexer {
public:
    Lexer(const std::string& src);
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
    void scanToken();
    void number();
    void identifier();
};

} // namespace delta