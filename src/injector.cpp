#include <syntax-tree.h>
#include <io-buffer.h>
#include <iostream>

namespace SyntaxTree
{
    Injector::Injector(const char *injectFile)
    {
        this->injectFile = injectFile;
        auto fileReader = new IOBuffer::IOFileReader(this->injectFile);
        this->charStream = new IOBuffer::CharStream(fileReader);
    }

    void Injector::inject(IOBuffer::IOBuffer *buffer)
    {
        auto ioWriter = new IOBuffer::IOMemoryBuffer(4096);
        char* curSymbol = this->charStream->getNext();
        while (curSymbol != nullptr) {
            if (*curSymbol == '@') {
                ioWriter->write(curSymbol, 1);
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
                    bool startWithIndent = true;
                    while (nRead > 0) {
                        if (startWithIndent) {
                            ioWriter->write("        ", 8);
                            startWithIndent = false;
                        }
                        const char* strIntended = this->injectIndent(strBuffer, 8);
                        if (strIntended[strlen(strIntended) - 1] == '\n') {
                            startWithIndent = true;
                        }
                        ioWriter->write((char*) strIntended, strlen(strIntended));
                        std::free((char*) strIntended);
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

        // skip while not found (@syntax-tree: stop-autogenerate)
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

        std::string strStopAutogenerateTag = "        // @syntax-tree: stop-autogenerate\n";
        ioWriter->write((char*) strStopAutogenerateTag.c_str(), strStopAutogenerateTag.length());

        curSymbol = this->charStream->getNext();
        while (curSymbol != nullptr) {
            ioWriter->write(curSymbol, 1);
            curSymbol = this->charStream->getNext();
        }

        auto fileWriter = new IOBuffer::IOFileWriter(this->injectFile, "w+");

        do {
            int nRead;
            char *tbuffer = (char *) malloc(sizeof(char) * 1024);
            do {
                memset(tbuffer, 0, sizeof(char) * 1024);
                nRead = ioWriter->read(tbuffer, 1023);
                if (nRead > 0) {
                    fileWriter->write(tbuffer, strlen(tbuffer));
                }
            } while (nRead != 0);
        } while(false);
    }

    const char* Injector::injectIndent(const char* src, int size)
    {
        int strSize = strlen(src) + 32;
        char* dst = (char*) malloc(sizeof(char) * strSize);
        memset(dst, 0, sizeof(char) * strSize);
        int lastStartCopyPos = 0;
        int writePos = 0;
        for (int i = 0; i < strlen(src); i++) {
            if (src[i] == '\n') {
                if (strlen(src) > i + 1 && src[i+1] == '\n') {
                    continue;
                }
                i++;
                if (strlen(src) > i) {
                    if (writePos + (i - lastStartCopyPos) + size >= strSize) {
                        strSize = writePos + (i - lastStartCopyPos) + size + 1;
                        dst = (char*) realloc(dst, sizeof(char) * strSize);
                    }

                    memcpy(dst + writePos, src + lastStartCopyPos, sizeof(char) * (i - lastStartCopyPos));
                    writePos += (i - lastStartCopyPos);
                    lastStartCopyPos = i;
                    memset(dst + writePos, 0x20, size * sizeof(char));
                    writePos += size;
                }
            }
        }

        if (strlen(src) > lastStartCopyPos) {
            if (writePos + (strlen(src) - lastStartCopyPos) >= strSize) {
                strSize = writePos + (strlen(src) - lastStartCopyPos) + 1;
                dst = (char*) realloc(dst, sizeof(char) * strSize);
                memset(dst + writePos, 0, sizeof(char) * (strSize - writePos));
            }

            memcpy(dst + writePos, src + lastStartCopyPos, sizeof(char) * (strlen(src) - lastStartCopyPos));
        }

        return dst;
    }
}
