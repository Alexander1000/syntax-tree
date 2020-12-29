#include <syntax-tree.h>
#include <io-buffer.h>

int main(int argc, char** argv) {
    IOBuffer::IOFileReader reader(argv[1]);
    IOBuffer::CharStream charStream(&reader);
    SyntaxTree::Lexer lexer(&charStream);
    lexer.getNextToken();
    return 0;
}
