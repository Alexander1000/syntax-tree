#include <syntax-tree.h>
#include <stack>

namespace SyntaxTree
{
    Lexer::Lexer(IOBuffer::CharStream *stream)
    {
        this->charStream = stream;
        this->position = new Position(0, 0);

        this->charStack = new std::stack<char*>;
        this->positionStack = new std::stack<Position*>;
    }

    Token::Token* Lexer::getNextToken()
    {
        char* curSymbol = this->getNextChar();
        if (curSymbol == nullptr) {
            return nullptr;
        }

        Token::Token* token = nullptr;
        IOBuffer::IOMemoryBuffer* ioWriter = nullptr;

        while (curSymbol != nullptr) {
            if (*curSymbol == '#') {
                // skip comments
                do {
                    curSymbol = this->getNextChar();
                } while (curSymbol != nullptr && *curSymbol != '\n');
                curSymbol = this->getNextChar();
                continue;
            }

            curSymbol = this->getNextChar();
        }

        return token;
    }

    char* Lexer::getNextChar()
    {
        if (!this->charStack->empty()) {
            char* symbol = this->charStack->top();
            this->charStack->pop();
            // todo: free current position
            this->position = this->positionStack->top();
            this->positionStack->pop();
            return symbol;
        }

        char* nextChar = this->charStream->getNext();
        if (nextChar != nullptr) {
            if (*nextChar == 0x0A || *nextChar == 0x0D) {
                this->position->setColumn(0);
                this->position->setLine(this->position->getLine() + 1);
            } else {
                this->position->setColumn(this->position->getColumn() + 1);
            }
        }

        return nextChar;
    }

    void Lexer::pushStackChar(char* curChar) {
        this->charStack->push(curChar);
        auto p = new Position(this->position->getLine(), this->position->getColumn());
        this->positionStack->push(p);
    }
}
