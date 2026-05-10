#include <iostream>
#include <vector>
#include <fstream>
#include "Lexer.h"

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return "";
	}
    // 获取文件大小
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string content(size, '\0');
    if (file.read(&content[0], size)) {
        return content;
    }
    throw std::runtime_error("读取文件失败: " + filename);
}

int main(int argc,char* argv[]) {
    std::string source = R"(
        block main {
            output content:"Hello, KZ!"
        }
    )";

    Lexer lexer(source);
    auto tokens = lexer.tokenize();

    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i].type == TokenType::OUTPUT) {
            if (i+3 < tokens.size() &&
                tokens[i+1].type == TokenType::CONTENT &&
                tokens[i+2].type == TokenType::COLON &&
                tokens[i+3].type == TokenType::STRING) {
                std::string msg = std::get<std::string>(tokens[i+3].value);
                std::cout << msg << std::endl;
            }
        }
    }

    return 0;
}