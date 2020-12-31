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
                    int nRead = 0;
                    char* strBuffer = (char*) malloc(sizeof(char) * 1025);
                    memset(strBuffer, 0, sizeof(char) * 1025);
                    nRead = buffer->read(strBuffer, 1024);
                    while (nRead > 0) {
                        ioWriter->write(strBuffer, nRead);
                        memset(strBuffer, 0, sizeof(char) * 1025);
                        nRead = buffer->read(strBuffer, 1024);
                    }
                    break;
                }
            } else {
                ioWriter->write(curSymbol, 1);
            }
            curSymbol = this->charStream->getNext();
        }

        curSymbol = this->charStream->getNext();
        while (curSymbol != nullptr) {
            if (*curSymbol == '@') {
                int tagLength = 0;
                auto ioTagReader = new IOBuffer::IOMemoryBuffer(64);
                while (curSymbol != nullptr && *curSymbol != '\n') {
                    ioTagReader->write(curSymbol, 1);
                    curSymbol = this->charStream->getNext();
                    tagLength++;
                }
                char* strTagValue = (char*) malloc(sizeof(char) * (tagLength + 1));
                memset(strTagValue, 0, sizeof(char) * (tagLength + 1));
                ioTagReader->read(strTagValue, tagLength);

                if (strcmp(strTagValue, "@syntax-tree: stop-autogenerate") == 0) {
                    break;
                }
            }
            curSymbol = this->charStream->getNext();
        }

        std::string strStopAutogenerateTag = "// @syntax-tree: stop-autogenerate\n";
        ioWriter->write((char*) strStopAutogenerateTag.c_str(), strStopAutogenerateTag.length());

        curSymbol = this->charStream->getNext();
        while (curSymbol != nullptr) {
            ioWriter->write(curSymbol, 1);
            curSymbol = this->charStream->getNext();
        }

        do {
            int nRead;
            char *tbuffer = (char *) malloc(sizeof(char) * 1024);
            do {
                memset(tbuffer, 0, sizeof(char) * 1024);
                nRead = ioWriter->read(tbuffer, 1023);
                if (nRead > 0) {
                    std::cout << tbuffer;
                }
            } while (nRead != 0);
        } while(false);

        std::cout << std::endl;
    }
}
