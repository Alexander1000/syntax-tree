#include <syntax-tree.h>

namespace SyntaxTree::Token
{
    OpenBraceToken::OpenBraceToken(int line, int column) : Token(line, column, nullptr)
    {
    }

    int OpenBraceToken::getType() {
        return Type::OpenBraceType;
    }
}
