#ifndef SYNTAX_TREE_TOKEN_INCLUDE_H
#define SYNTAX_TREE_TOKEN_INCLUDE_H

#include <io-buffer.h>
#include <map>
#include <string>

namespace SyntaxTree::Token
{
    enum Type {
        TypeType,
        NameType,
        OpenType,
        CloseType,
        OpenBraceType,
        CloseBraceType,
        DoubleDotType,
    };

    class TokenMap
    {
    public:
        TokenMap();
        Type getType(const char*);
        const char* getName(Type);
    private:
        std::map<std::string, Type>* tokenMap;
    };

    class Token
    {
    public:
        Token(int line, int column, IOBuffer::IOReader *reader);
        int getLine();
        int getColumn();
        virtual Type getType() = 0;
        IOBuffer::IOReader* getReader();
    protected:
        int line;
        int column;
        IOBuffer::IOReader *reader;
    };
}

#endif
