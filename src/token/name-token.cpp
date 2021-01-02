#include <syntax-tree.h>
#include <io-buffer.h>

namespace SyntaxTree::Token
{
    NameToken::NameToken(int line, int column, IOBuffer::IOReader *reader) : Token(line, column, reader) {
    }

    int NameToken::getType() {
        return Type::NameType;
    }
}
