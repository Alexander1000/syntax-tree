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

            for (auto & itMatch : *matches) {
                if (itCopy == elements->end()) {
                    foundMatchRule = false;
                    break;
                }

                auto quantity = itMatch->getQuantity();

                if (quantity == nullptr) {
                    if (Tree::check_match_rule(*itCopy, itMatch)) {
                        ruleMatches->push_back(*itCopy);
                    } else {
                        foundMatchRule = false;
                        break;
                    }
                } else {
                    switch (quantity->getType()) {
                        case QuantityType::OneOrMoreMatchType: {
                            break;
                        }
                        default: {
                            // not supported yet
                            throw std::exception();
                        }
                    }
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

    bool Tree::check_match_rule(SyntaxElement* syntaxElement, RuleMatch* ruleMatch)
    {
        switch(ruleMatch->getType()) {
            case RuleMatchType::RuleMatchTokenType: {
                if (syntaxElement->getType() == SyntaxElementType::TokenType) {
                    auto token = syntaxElement->getToken();
                    if (token->getType() == ruleMatch->getTokenType()) {
                        auto tv = ruleMatch->getValue();
                        if (tv != nullptr) {
                            char* strValue = (char*) malloc(sizeof(char) * 16);
                            memset(strValue, 0, sizeof(char) * 16);
                            auto reader = (IOBuffer::IOMemoryBuffer*) token->getReader();
                            reader->setPosition(0);
                            reader->read(strValue, 15);
                            if (strcmp(tv, strValue) == 0) {
                                return true;
                            }
                        } else {
                            return true;
                        }
                    }
                }
                break;
            }
            case RuleMatchType::RuleMatchName: {
                if (syntaxElement->getType() == SyntaxElementType::SyntaxType) {
                    auto ruleElement = syntaxElement->getRule();
                    if (ruleElement != nullptr) {
                        if (strcmp(ruleElement->getName(), ruleMatch->getRuleName()) == 0) {
                            return true;
                        }
                    }
                }
                break;
            }
        }

        return false;
    }
}
