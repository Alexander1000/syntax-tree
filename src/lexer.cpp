#include <syntax-tree.h>

namespace SyntaxTree
{
    Lexer::Lexer(IOBuffer::CharStream *stream) {
        this->charStream = stream;
    }
}
