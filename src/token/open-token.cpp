#include <syntax-tree.h>

namespace SyntaxTree::Token
{
    OpenToken::OpenToken(int line, int column) : Token(line, column, nullptr)
    {
    }

    int OpenToken::getType() {
        return Type::OpenType;
    }
}
