#include <syntax-tree.h>

namespace SyntaxTree::Token
{
    DoubleDotToken::DoubleDotToken(int line, int column) : Token(line, column, nullptr)
    {
    }

    int DoubleDotToken::getType() {
        return Type::DoubleDotType;
    }
}
