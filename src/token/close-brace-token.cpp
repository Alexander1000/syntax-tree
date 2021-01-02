#include <syntax-tree.h>

namespace SyntaxTree::Token
{
    CloseBraceToken::CloseBraceToken(int line, int column) : Token(line, column, nullptr)
    {
    }

    int CloseBraceToken::getType() {
        return Type::CloseBraceType;
    }
}
