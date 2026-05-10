#include "Lexer.h"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(const std::string& src) : source(src) {}

char Lexer::currentChar() {
    if (pos >= source.size()) return '\0';
    return source[pos];
}

void Lexer::advance() {
    if (currentChar() == '\n') { line++; col = 1; }
    else col++;
    pos++;
}

void Lexer::skipWhitespace() {
    while (std::isspace(currentChar())) advance();
}

Token Lexer::readIdentifierOrKeyword() {
    std::string ident;
    while (std::isalnum(currentChar()) || currentChar() == '_') {
        ident += currentChar();
        advance();
    }
    if (ident == "block") return Token(TokenType::BLOCK, ident, line, col - ident.size());
    if (ident == "main")  return Token(TokenType::MAIN, ident, line, col - ident.size());
    if (ident == "output")return Token(TokenType::OUTPUT, ident, line, col - ident.size());
    if (ident == "content")return Token(TokenType::CONTENT, ident, line, col - ident.size());
    return Token(TokenType::IDENTIFIER, ident, line, col - ident.size());
}

Token Lexer::readString() {
    advance();
    std::string str;
    while (currentChar() != '"' && currentChar() != '\0') {
        str += currentChar();
        advance();
    }
    if (currentChar() == '"') advance();
    return Token(TokenType::STRING, str, line, col - str.size() - 2);
}

Token Lexer::nextToken() {
    skipWhitespace();
    if (pos >= source.size()) return Token(TokenType::END, "", line, col);
    char ch = currentChar();
    if (std::isalpha(ch) || ch == '_') return readIdentifierOrKeyword();
    if (ch == '"') return readString();
    if (ch == '{') { advance(); return Token(TokenType::LBRACE, "{", line, col-1); }
    if (ch == '}') { advance(); return Token(TokenType::RBRACE, "}", line, col-1); }
    if (ch == ':') { advance(); return Token(TokenType::COLON, ":", line, col-1); }
    throw std::runtime_error("Unexpected character");
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token tok = nextToken();
    while (tok.type != TokenType::END) {
        tokens.push_back(tok);
        tok = nextToken();
    }
    return tokens;
}