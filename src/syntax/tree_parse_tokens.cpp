#include <syntax-tree.h>
#include <list>
#include <cstring>
#include <iostream>

namespace SyntaxTree::Syntax
{
    SyntaxElement* Tree::parse(std::list<SyntaxTree::Token::Token*> *tokens)
    {
        auto syntaxElements = new std::list<SyntaxElement*>;
        for (auto it = tokens->begin(); it != tokens->end(); it++) {
            syntaxElements->push_back(new SyntaxElement(*it));
        }
        return this->beforeParse(syntaxElements);
    }

    SyntaxElement* Tree::beforeParse(std::list<SyntaxElement *> *elements) {
        return this->parse(elements);
    }

    SyntaxElement* Tree::parse(std::list<SyntaxElement*>* elements)
    {
        if (elements->size() == 1) {
            return *elements->begin();
        }

        int sizeElements;

        for (auto it = this->rules->begin(); it != this->rules->end(); it++) {
            Rule *rule = *it;
            do {
                sizeElements = elements->size();
                elements = this->run_rule(rule, elements);
            } while (sizeElements != elements->size());
        }

        return this->parse(elements);
    }

    std::list<SyntaxElement*>* Tree::run_rule(Rule *rule, std::list<SyntaxElement*> *elements)
    {
        auto filteredElements = new std::list<SyntaxElement*>;

        auto matches = rule->getMatches();

        for (auto it = elements->begin(); it != elements->end(); it++) {
            auto itCopy = it;
            auto ruleMatches = new std::list<SyntaxElement*>;
            bool foundMatchRule = true;

            for (auto itMatch = matches->begin(); itMatch != matches->end(); itMatch++) {
                if (itCopy == elements->end()) {
                    foundMatchRule = false;
                    break;
                }

                bool success = true;

                switch((*itMatch)->getType()) {
                    case RuleMatchType::RuleMatchTokenType: {
                        if ((*itCopy)->getType() == SyntaxElementType::TokenType) {
                            auto token = (*itCopy)->getToken();
                            if (token->getType() == (*itMatch)->getTokenType()) {
                                auto tv = (*itMatch)->getValue();
                                if (tv != nullptr) {
                                    char* strValue = (char*) malloc(sizeof(char) * 16);
                                    memset(strValue, 0, sizeof(char) * 16);
                                    auto reader = (IOBuffer::IOMemoryBuffer*) token->getReader();
                                    reader->setPosition(0);
                                    reader->read(strValue, 15);
                                    if (strcmp(tv, strValue) == 0) {
                                        ruleMatches->push_back(*itCopy);
                                        break;
                                    }
                                } else {
                                    ruleMatches->push_back(*itCopy);
                                    break;
                                }
                            }
                        }
                        success = false;
                        break;
                    }
                    case RuleMatchType::RuleMatchName: {
                        if ((*itCopy)->getType() == SyntaxElementType::SyntaxType) {
                            auto ruleElement = (*itCopy)->getRule();
                            if (ruleElement != nullptr) {
                                if (strcmp(ruleElement->getName(), (*itMatch)->getRuleName()) == 0) {
                                    ruleMatches->push_back(*itCopy);
                                    break;
                                }
                            }
                        }
                        success = false;
                        break;
                    }
                }

                if (!success) {
                    foundMatchRule = false;
                    break;
                }

                itCopy++;
            }

            if (foundMatchRule) {
                auto element = new SyntaxElement(ruleMatches);
                element->setRule(rule);
                auto rootElement = new SyntaxElement(element);
                rootElement->setRule(rule);
                filteredElements->push_back(rootElement);

                for (auto itRule = ruleMatches->begin(); itRule != ruleMatches->end(); itRule++) {
                    // skip elements
                    it++;
                }
                it--;
            } else {
                filteredElements->push_back(*it);
            }
        }

        delete elements;
        return filteredElements;
    }
}
