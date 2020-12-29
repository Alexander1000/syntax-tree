#include <syntax-tree.h>
#include <io-buffer.h>

namespace SyntaxTree::Render
{
    Render::Render()
    {
    }

    void Render::renderTree(IOBuffer::IOBuffer *buffer, SyntaxTree::Syntax::SyntaxElement *tree)
    {
        if (tree->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
            this->renderTree(buffer, tree->getElement());
            return;
        }
    }
}
