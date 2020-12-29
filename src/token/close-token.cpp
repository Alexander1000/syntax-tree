#include <syntax-tree.h>

namespace SyntaxTree::Token
{
    CloseToken::CloseToken(int line, int column) : Token(line, column, nullptr)
    {
    }

    Type CloseToken::getType() {
        return Type::CloseType;
    }
}
