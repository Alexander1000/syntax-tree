#ifndef SYNTAX_TREE_RENDER_INCLUDE_H
#define SYNTAX_TREE_RENDER_INCLUDE_H

#include <syntax-tree/syntax.h>
#include <io-buffer.h>
#include <list>

namespace SyntaxTree::Render
{
    class Render
    {
    public:
        Render();
        void renderTree(IOBuffer::IOBuffer* buffer, SyntaxTree::Syntax::SyntaxElement* tree);
        void renderTree(IOBuffer::IOBuffer* buffer, SyntaxTree::Syntax::Rule* rule, std::list<SyntaxTree::Syntax::SyntaxElement*>* elements);

    private:
        int lastNumberOfRecord;

        void renderRecord(IOBuffer::IOBuffer* buffer, SyntaxTree::Token::Token* tokenName, SyntaxTree::Syntax::SyntaxElement* rulesTree, int numberOfRecord);
        void renderRuleRecord(IOBuffer::IOBuffer* buffer, SyntaxTree::Syntax::SyntaxElement* syntaxElement, int numberOfRecord);
    };
}

#endif
