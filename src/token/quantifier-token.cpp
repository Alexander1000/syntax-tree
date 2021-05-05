#include <syntax-tree.h>
#include <io-buffer.h>

namespace SyntaxTree::Token
{
    QuantifierToken::QuantifierToken(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader)
    {
    }

    int QuantifierToken::getType() {
        return Type::QuantifierType;
    }
}
