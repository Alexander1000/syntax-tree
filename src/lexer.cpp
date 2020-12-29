#include <syntax-tree.h>
#include <stack>

namespace SyntaxTree
{
    Lexer::Lexer(IOBuffer::CharStream *stream)
    {
        this->charStream = stream;
        this->position = new Position(0, 0);
        this->mode = Mode::MainMode;

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

            if (*curSymbol == 0x20 || *curSymbol == '\n') {
                // skip spaces
                do {
                    curSymbol = this->getNextChar();
                } while(curSymbol != nullptr && (*curSymbol == 0x20 || *curSymbol == '\n'));
                continue;
            }

            switch (this->mode) {
                case Mode::MainMode: {
                    if (*curSymbol == '[') {
                        // open token
                        this->mode = Mode::InnerMode;
                        token = new Token::OpenToken(this->position->getLine(), this->position->getColumn());
                        return token;
                    }

                    if (*curSymbol == ']') {
                        // close token
                        token = new Token::CloseToken(this->position->getLine(), this->position->getColumn());
                        return token;
                    }

                    ioWriter = new IOBuffer::IOMemoryBuffer(16);
                    while (curSymbol != nullptr && *curSymbol != 0x20) {
                        ioWriter->write(curSymbol, 1);
                        curSymbol = this->getNextChar();
                    }
                    // token name rule
                    token = new Token::NameToken(this->position->getLine(), this->position->getColumn(), ioWriter);
                    return token;
                }
                case Mode::InnerMode: {
                    ioWriter = new IOBuffer::IOMemoryBuffer(3);
                    while (curSymbol != nullptr && *curSymbol >= 'a' && *curSymbol <= 'z') {
                        ioWriter->write(curSymbol, 1);
                        curSymbol = this->getNextChar();
                    }
                    // token name rule
                    token = new Token::TypeToken(this->position->getLine(), this->position->getColumn(), ioWriter);
                    this->mode = Mode::RuleMode;
                    return token;
                }
                case Mode::RuleMode: {
                    if (*curSymbol == ':') {
                        token = new Token::DoubleDotToken(this->position->getLine(), this->position->getColumn());
                        return token;
                    }

                    if (*curSymbol == '(') {
                        this->mode = Mode::RuleArgsMode;
                        token = new Token::OpenBraceToken(this->position->getLine(), this->position->getColumn());
                        return token;
                    }

                    ioWriter = new IOBuffer::IOMemoryBuffer(16);
                    while (curSymbol != nullptr && *curSymbol != 0x20) {
                        ioWriter->write(curSymbol, 1);
                        curSymbol = this->getNextChar();
                    }
                    // token name rule
                    token = new Token::NameToken(this->position->getLine(), this->position->getColumn(), ioWriter);
                    return token;
                }
                case Mode::RuleArgsMode: {
                    if (*curSymbol == ')') {
                        this->mode = Mode::RuleMode;
                        token = new Token::CloseBraceToken(this->position->getLine(), this->position->getColumn());
                        return token;
                    }
                    break;
                }
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
