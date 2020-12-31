#include <syntax-tree.h>
#include <io-buffer.h>
#include <iostream>

namespace SyntaxTree
{
    Injector::Injector(const char *injectFile)
    {
        auto fileReader = new IOBuffer::IOFileReader(injectFile);
        this->charStream = new IOBuffer::CharStream(fileReader);
    }

    void Injector::inject(IOBuffer::IOBuffer *buffer)
    {
        auto ioWriter = new IOBuffer::IOMemoryBuffer(4096);
        char* curSymbol = this->charStream->getNext();
        while (curSymbol != nullptr) {
            if (*curSymbol == '@') {
                int tagLength = 0;
                auto ioTagReader = new IOBuffer::IOMemoryBuffer(64);
                while (curSymbol != nullptr && *curSymbol != '\n') {
                    ioTagReader->write(curSymbol, 1);
                    curSymbol = this->charStream->getNext();
                    tagLength++;
                    ioWriter->write(curSymbol, 1);
                }
                ioWriter->write(curSymbol, 1);
                char* strTagValue = (char*) malloc(sizeof(char) * (tagLength + 1));
                memset(strTagValue, 0, sizeof(char) * (tagLength + 1));
                ioTagReader->read(strTagValue, tagLength);

                if (strcmp(strTagValue, "@syntax-tree: start-autogenerate") == 0) {
                    // do start
                }
                std::cout << strTagValue << std::endl;
            } else {
                ioWriter->write(curSymbol, 1);
            }
            curSymbol = this->charStream->getNext();
        }
    }
}
