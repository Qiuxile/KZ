#pragma once
#include <string>
#include <variant>

enum class TokenType {
    BLOCK, MAIN,
    OUTPUT, CONTENT,
    IDENTIFIER, STRING,
    COLON, LBRACE, RBRACE,
    END
};

struct Token {
    TokenType type;
    std::variant<std::string, int> value;
    int line, col;

    Token(TokenType t, const std::string& v = "", int l = 1, int c = 1)
        : type(t), value(v), line(l), col(c) {}
    Token(TokenType t, int v, int l, int c) : type(t), value(v), line(l), col(c) {}
};