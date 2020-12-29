#include <syntax-tree.h>
#include <io-buffer.h>

namespace SyntaxTree::Token
{
    TypeToken::TypeToken(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    Type TypeToken::getType() {
        return Type::TypeType;
    }
}
