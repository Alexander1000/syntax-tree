#include <syntax-tree.h>

namespace SyntaxTree::Token
{
    CloseToken::CloseToken(int line, int column) : Token(line, column, nullptr)
    {
    }

    int CloseToken::getType() {
        return Type::CloseType;
    }
}
