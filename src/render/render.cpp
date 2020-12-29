#include <syntax-tree.h>
#include <io-buffer.h>
#include <list>

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

        if (tree->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
            this->renderTree(buffer, tree->getRule(), tree->getListElements());
            return;
        }
    }

    void Render::renderTree(IOBuffer::IOBuffer *buffer, SyntaxTree::Syntax::Rule* rule, std::list<SyntaxTree::Syntax::SyntaxElement*>* elements)
    {
        
    }
}
