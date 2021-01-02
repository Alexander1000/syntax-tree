#include <syntax-tree.h>
#include <io-buffer.h>
#include <list>
#include <iostream>

namespace SyntaxTree::Render
{
    Render::Render()
    {
        this->lastNumberOfRecord = 0;
    }

    void Render::renderTree(IOBuffer::IOBuffer *buffer, SyntaxTree::Syntax::SyntaxElement *tree)
    {
        if (tree->getType() == SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
            this->renderTree(buffer, tree->getElement());
            return;
        }

        if (tree->getType() == SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
            this->renderTree(buffer, tree->getRule(), tree->getListElements());
            return;
        }
    }

    void Render::renderTree(IOBuffer::IOBuffer *buffer, SyntaxTree::Syntax::Rule* rule, std::list<SyntaxTree::Syntax::SyntaxElement*>* elements)
    {
        if (strcmp(rule->getName(), "tree") == 0) {
            for (auto it = elements->begin(); it != elements->end(); it++) {
                this->renderTree(buffer, *it);
            }
        }

        if (strcmp(rule->getName(), "record") == 0) {
            auto it = elements->begin(); // token with name
            auto tokenNameElement = *it;
            it++; // [ - open token
            it++; // rule/ruleList
            auto rulesTree = *it;
            it++; // ] - close token

            if (tokenNameElement->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenType) {
                // todo: make another error
                throw new SyntaxTree::Token::UnknownToken;
            }

            this->renderRecord(buffer, tokenNameElement->getToken(), rulesTree, this->lastNumberOfRecord++);
            buffer->write("\n", 1);
            return;
        }
    }

    void Render::renderRecord(
        IOBuffer::IOBuffer *buffer,
        SyntaxTree::Token::Token *tokenName,
        SyntaxTree::Syntax::SyntaxElement *rulesTree,
        int numberOfRecord
    ) {
        // render record
        auto reader = (IOBuffer::IOMemoryBuffer*) tokenName->getReader();
        reader->setPosition(0);
        char* strRuleName = (char*) malloc(sizeof(char) * 32);
        memset(strRuleName, 0, sizeof(char) * 32);
        reader->read(strRuleName, 32);
        char* strMatchRule = (char*) malloc(sizeof(char) * 1024);
        memset(strMatchRule, 0, sizeof(char) * 1024);
        sprintf(strMatchRule, "auto rule%02d = new SyntaxTree::Syntax::Rule(\"%s\");\n", numberOfRecord, strRuleName);
        buffer->write(strMatchRule, strlen(strMatchRule));

        if (rulesTree->getType() != SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
            throw new SyntaxTree::Token::UnknownToken;
        }
        auto sntxRuleTree = rulesTree->getElement();
        if (sntxRuleTree->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
            throw new SyntaxTree::Token::UnknownToken;
        }
        auto rule = sntxRuleTree->getRule();
        if (strcmp(rule->getName(), "ruleList") == 0) {
            auto rulesListElements = sntxRuleTree->getListElements();

            for (auto it = rulesListElements->begin(); it != rulesListElements->end(); it++) {
                auto sntxRuleElement = *it;
                if (sntxRuleElement->getType() != SyntaxTree::Syntax::SyntaxElementType::SyntaxType) {
                    throw new SyntaxTree::Token::UnknownToken;
                }
                auto ruleElement = sntxRuleElement->getElement();
                this->renderRuleRecord(buffer, ruleElement, numberOfRecord);
            }
        } else if (strcmp(rule->getName(), "rule") == 0) {
            this->renderRuleRecord(buffer, sntxRuleTree, numberOfRecord);
        }

        char* strAddRuleToList = (char*) malloc(sizeof(char) * 1024);
        memset(strAddRuleToList, 0, sizeof(char) * 1024);
        sprintf(strAddRuleToList, "this->rules->push_back(rule%02d);\n", numberOfRecord);
        buffer->write(strAddRuleToList, strlen(strAddRuleToList));
    }

    void Render::renderRuleRecord(IOBuffer::IOBuffer *buffer, SyntaxTree::Syntax::SyntaxElement* syntaxElement, int numberOfRecord)
    {
        auto rule = syntaxElement->getRule();
        if (strcmp(rule->getName(), "ruleList") == 0) {
            if (syntaxElement->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
                throw new SyntaxTree::Token::UnknownToken;
            }
            auto ruleListSyntax = syntaxElement->getListElements();
            for (auto it = ruleListSyntax->begin(); it != ruleListSyntax->end(); it++) {
                auto nestedRule = *it;
                this->renderRuleRecord(buffer, nestedRule->getElement(), numberOfRecord);
            }
            return;
        }
        if (strcmp(rule->getName(), "rule") == 0) {
            if (syntaxElement->getType() != SyntaxTree::Syntax::SyntaxElementType::TokenListType) {
                throw new SyntaxTree::Token::UnknownToken;
            }
            auto ruleListSyntax = syntaxElement->getListElements();
            auto it = ruleListSyntax->begin(); // type
            auto tokenType = (*it)->getToken();
            auto reader = (IOBuffer::IOMemoryBuffer*) tokenType->getReader();
            reader->setPosition(0);
            char* strType = (char*) malloc(sizeof(char) * 2);
            memset(strType, 0, sizeof(char) * 2);
            reader->read(strType, 1);
            it++; // : - double dot token
            it++; // name of rule
            auto tokenName = (*it)->getToken();
            reader = (IOBuffer::IOMemoryBuffer*) tokenName->getReader();
            reader->setPosition(0);
            char* strName = (char*) malloc(sizeof(char) * 64);
            memset(strName, 0, sizeof(char) * 64);
            reader->read(strName, 63);

            char* strInnerRule = (char*) malloc(sizeof(char) * 1024);
            memset(strInnerRule, 0, sizeof(char) * 1024);

            if (strcmp(strType, "s") == 0) {
                sprintf(strInnerRule, "\"%s\"", strName);
            }
            if (strcmp(strType, "t") == 0) {
                if (std::next(it) != ruleListSyntax->end()) {
                    it++; // ( - token
                    it++; // match token value
                    auto matchValueToken = (*it)->getToken();
                    reader = (IOBuffer::IOMemoryBuffer*) matchValueToken->getReader();
                    reader->setPosition(0);
                    char* strValue = (char*) malloc(sizeof(char) * 64);
                    memset(strValue, 0, sizeof(char) * 64);
                    reader->read(strValue, 63);
                    it++; // ) - token
                    sprintf(strInnerRule, "this->tokenMap->getType(\"%s\"), \"%s\"", strName, strValue);
                } else {
                    sprintf(strInnerRule, "this->tokenMap->getType(\"%s\")", strName);
                }
            }

            // make final record
            char* strRuleRecord = (char*) malloc(sizeof(char) * 1024);
            memset(strRuleRecord, 0, sizeof(char) * 1024);
            sprintf(strRuleRecord, "rule%02d->addMatch(new SyntaxTree::Syntax::RuleMatch(%s));\n", numberOfRecord, strInnerRule);
            buffer->write(strRuleRecord, strlen(strRuleRecord));
        }
    }
}
