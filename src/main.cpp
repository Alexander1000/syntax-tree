#include <syntax-tree.h>
#include <io-buffer.h>
#include <iostream>
#include <list>

int main(int argc, char** argv) {
    SyntaxTree::Config config(argc, argv);
    if (config.isHelp()) {
        std::cout << config.getHelpText() << std::endl;
        return 0;
    }

    if (config.getSyntaxFile() == nullptr) {
        std::cout << "Not set syntax file" << std::endl;
        std::cout << config.getHelpText() << std::endl;
        return -1;
    }

    if (config.getInjectFile() == nullptr) {
        std::cout << "Not set inject file" << std::endl;
        std::cout << config.getHelpText() << std::endl;
        return -1;
    }

    IOBuffer::IOFileReader reader(config.getSyntaxFile());
    IOBuffer::CharStream charStream(&reader);
    SyntaxTree::Lexer lexer(&charStream);
    auto tokenList = new std::list<SyntaxTree::Token::Token*>;
    auto token = lexer.getNextToken();
    while (token != nullptr) {
        tokenList->push_back(token);
        token = lexer.getNextToken();
    }
    auto tree = new SyntaxTree::Syntax::Tree;
    auto syntaxTree = tree->parse(tokenList);
    auto render = new SyntaxTree::Render::Render;
    auto output = new IOBuffer::IOMemoryBuffer(4096);
    render->renderTree(output, syntaxTree);

    int nRead;
    char* buffer = (char*) malloc(sizeof(char) * 1024);
    do {
        memset(buffer, 0, sizeof(char) * 1024);
        nRead = output->read(buffer, 1023);
        if (nRead > 0) {
            std::cout << buffer;
        }
    } while(nRead != 0);

    std::cout << std::endl;

    return 0;
}
