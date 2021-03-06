#include <syntax-tree.h>
#include <io-buffer.h>

namespace SyntaxTree::Token
{
    Token::Token(int line, int column, IOBuffer::IOReader *reader) {
        this->line = line;
        this->column = column;
        this->reader = reader;
    }

    IOBuffer::IOReader* Token::getReader() {
        return this->reader;
    }

    int Token::getColumn() {
        return this->column;
    }

    int Token::getLine() {
        return this->line;
    }
}
