#include <syntax-tree.h>

namespace SyntaxTree::Token
{
    DoubleDotToken::DoubleDotToken(int line, int column) : Token(line, column, nullptr)
    {
    }

    Type DoubleDotToken::getType() {
        return Type::DoubleDotType;
    }
}
