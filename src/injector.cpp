#include <syntax-tree.h>
#include <io-buffer.h>

namespace SyntaxTree
{
    Injector::Injector(const char *injectFile)
    {
        auto fileReader = new IOBuffer::IOFileReader(injectFile);
        this->charStream = new IOBuffer::CharStream(fileReader);
    }

    void Injector::inject(IOBuffer::IOBuffer *buffer)
    {
        
    }
}
