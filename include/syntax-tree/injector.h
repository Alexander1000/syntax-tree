#ifndef SYNTAX_TREE_INJECTOR_INCLUDE_H
#define SYNTAX_TREE_INJECTOR_INCLUDE_H

#include <io-buffer.h>

namespace SyntaxTree
{
    class Injector
    {
    public:
        Injector(const char* injectFile);
        void inject(IOBuffer::IOBuffer*);

    private:
        IOBuffer::CharStream* charStream;

        const char* injectIndent(const char* src, int size);
    };
}

#endif
