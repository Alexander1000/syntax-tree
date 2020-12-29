#include <syntax-tree.h>

namespace SyntaxTree::Token
{
    OpenBraceToken::OpenBraceToken(int line, int column) : Token(line, column, nullptr)
    {
    }

    Type OpenBraceToken::getType() {
        return Type::OpenBraceType;
    }
}
