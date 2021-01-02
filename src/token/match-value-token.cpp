#include <syntax-tree.h>
#include <io-buffer.h>

namespace SyntaxTree::Token
{
    MatchValueToken::MatchValueToken(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    int MatchValueToken::getType() {
        return Type::MatchValueType;
    }
}
