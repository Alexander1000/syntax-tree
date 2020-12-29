#include <syntax-tree.h>

namespace SyntaxTree
{
    Lexer::Lexer(IOBuffer::CharStream *stream) {
        this->charStream = stream;
    }

    Token::Token* Lexer::getNextToken()
    {
        return nullptr;
    }
}
