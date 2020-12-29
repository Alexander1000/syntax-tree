#ifndef SYNTAX_TREE_LEXER_INCLUDE_H
#define SYNTAX_TREE_LEXER_INCLUDE_H

#include <io-buffer.h>

namespace SyntaxTree
{
    class Lexer
    {
    public:
        Lexer(IOBuffer::CharStream*);

    private:
        IOBuffer::CharStream* charStream;
    };
}

#endif
