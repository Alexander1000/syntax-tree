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
            auto it = elements->begin(); // token with name
            auto tokenNameElement = *it;
            it++; // [ - open token
            it++; // rule/ruleList
            auto rulesTree = *it;
            it++; // ] - close token

            if (tokenNameElement->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                // todo: make another error
                throw new SyntaxTree::Token::UnknownToken;
            }

            this->renderRecord(buffer, tokenNameElement->getToken(), rulesTree, 0);
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
