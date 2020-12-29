#ifndef SYNTAX_TREE_TOKEN_INCLUDE_H
#define SYNTAX_TREE_TOKEN_INCLUDE_H

#include <io-buffer.h>
#include <map>
#include <string>

namespace SyntaxTree::Token
{
    class UnknownToken {};

    enum Type {
        TypeType,
        NameType,
        OpenType,
        CloseType,
        OpenBraceType,
        CloseBraceType,
        DoubleDotType,
        MatchValueType,
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

    class TypeToken : public Token
    {
    public:
        TypeToken(int line, int column, IOBuffer::IOReader *reader);
        Type getType() final;
    };

    class OpenToken : public Token
    {
    public:
        OpenToken(int line, int column);
        Type getType() final;
    };

    class CloseToken : public Token
    {
    public:
        CloseToken(int line, int column);
        Type getType() final;
    };

    class NameToken : public Token
    {
    public:
        NameToken(int line, int column, IOBuffer::IOReader *reader);
        Type getType() final;
    };

    class DoubleDotToken : public Token
    {
    public:
        DoubleDotToken(int line, int column);
        Type getType() final;
    };

    class OpenBraceToken : public Token
    {
    public:
        OpenBraceToken(int line, int column);
        Type getType() final;
    };

    class CloseBraceToken : public Token
    {
    public:
        CloseBraceToken(int line, int column);
        Type getType() final;
    };

    class MatchValueToken : public Token
    {
    public:
        MatchValueToken(int line, int column, IOBuffer::IOReader *reader);
        Type getType() final;
    };
}

#endif
