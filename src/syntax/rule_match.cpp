#include <syntax-tree.h>

namespace SyntaxTree::Syntax
{
    RuleMatch::RuleMatch(const char *ruleName)
    {
        this->value.ruleName = ruleName;
        this->type = RuleMatchType::RuleMatchName;
        this->tokenValue = nullptr;
    }

    RuleMatch::RuleMatch(SyntaxTree::Token::Type tokenType)
    {
        this->value.tokenType = tokenType;
        this->type = RuleMatchType::RuleMatchTokenType;
        this->tokenValue = nullptr;
    }

    RuleMatch::RuleMatch(SyntaxTree::Token::Type tokenType, const char* value)
    {
        this->value.tokenType = tokenType;
        this->type = RuleMatchType::RuleMatchTokenType;
        this->tokenValue = value;
    }

    const char * RuleMatch::getValue() {
        return this->tokenValue;
    }

    RuleMatchType RuleMatch::getType() {
        return this->type;
    }

    SyntaxTree::Token::Type RuleMatch::getTokenType() {
        return this->value.tokenType;
    }

    const char * RuleMatch::getRuleName() {
        return this->value.ruleName;
    }
}
