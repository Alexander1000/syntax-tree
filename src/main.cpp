#include <syntax-tree.h>
#include <io-buffer.h>
#include <iostream>
#include <list>

int main(int argc, char** argv) {
    IOBuffer::IOFileReader reader(argv[1]);
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
    auto buffer = new IOBuffer::IOMemoryBuffer(4096);
    render->renderTree(buffer, syntaxTree);
    return 0;
}
