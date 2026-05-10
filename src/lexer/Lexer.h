#pragma once
#include "Token.h"
#include <string>
#include <vector>

class Lexer {
public:
    Lexer(const std::string& source);
    Token nextToken();
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t pos = 0;
    int line = 1, col = 1;

    char currentChar();
    void advance();
    void skipWhitespace();
    Token readIdentifierOrKeyword();
    Token readString();
};