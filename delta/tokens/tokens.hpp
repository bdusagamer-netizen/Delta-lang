#pragma once
#include <string>

namespace delta {

enum class TokenType {
    IDENT,          // identifier
    NUMBER,         // numeric literal
    STRING,         // string literal

    LPAREN,         // (
    RPAREN,         // )
    LBRACE,         // {
    RBRACE,         // }
    COMMA,          // ,
    DOT,            // .
    OPERATOR,       // + - * / etc.

    END_OF_FILE     // end of input
};

struct Token {
    TokenType type;
    std::string text;
    int line;
    int column;
};

} // namespace delta