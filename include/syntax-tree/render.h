#ifndef SYNTAX_TREE_RENDER_INCLUDE_H
#define SYNTAX_TREE_RENDER_INCLUDE_H

#include <syntax-tree/syntax.h>
#include <io-buffer.h>

namespace SyntaxTree::Render
{
    class Render
    {
    public:
        Render();
        void renderTree(IOBuffer::IOBuffer* buffer, SyntaxTree::Syntax::SyntaxElement* tree);
    };
}

#endif
