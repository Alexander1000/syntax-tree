#include <syntax-tree.h>
#include <io-buffer.h>
#include <iostream>

int main(int argc, char** argv) {
    IOBuffer::IOFileReader reader(argv[1]);
    IOBuffer::CharStream charStream(&reader);
    SyntaxTree::Lexer lexer(&charStream);
    auto token = lexer.getNextToken();
    while (token != nullptr) {
        std::cout << "Type: " << token->getType() << std::endl;

        auto tReader = token->getReader();
        if (tReader != nullptr) {
            char *str = (char *) malloc(sizeof(char) * 1024);
            memset(str, 0, sizeof(char) * 1024);
            tReader->read(str, 1023);
            std::cout << "Token: " << str << std::endl;
        }
        token = lexer.getNextToken();
    }
    return 0;
}
