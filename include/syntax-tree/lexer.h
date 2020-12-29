#ifndef SYNTAX_TREE_LEXER_INCLUDE_H
#define SYNTAX_TREE_LEXER_INCLUDE_H

#include <io-buffer.h>
#include <syntax-tree/token.h>

namespace SyntaxTree
{
    class Lexer
    {
    public:
        Lexer(IOBuffer::CharStream*);
        Token::Token* getNextToken();

    private:
        IOBuffer::CharStream* charStream;
    };
}

#endif
