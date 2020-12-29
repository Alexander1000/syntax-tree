#include <syntax-tree.h>
#include <io-buffer.h>
#include <list>
#include <iostream>

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
        if (strcmp(rule->getName(), "tree") == 0) {
            for (auto it = elements->begin(); it != elements->end(); it++) {
                this->renderTree(buffer, *it);
            }
        }

        if (strcmp(rule->getName(), "record") == 0) {
            std::cout << std::endl;
            this->renderRecord(buffer, nullptr, nullptr, 0);
            return;
        }
    }

    void Render::renderRecord(
        IOBuffer::IOBuffer *buffer,
        SyntaxTree::Token::Token *tokenName,
        SyntaxTree::Syntax::SyntaxElement *rulesTree,
        int numberOfRecord
    ) {
        // render record
    }
}
