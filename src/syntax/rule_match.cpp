#include <syntax-tree.h>

namespace SyntaxTree::Syntax
{
    RuleMatch::RuleMatch(const char *ruleName)
    {
        this->value.ruleName = ruleName;
        this->type = RuleMatchType::RuleMatchName;
        this->tokenValue = nullptr;
        this->quantity = nullptr;
    }

    RuleMatch::RuleMatch(int tokenType)
    {
        this->value.tokenType = tokenType;
        this->type = RuleMatchType::RuleMatchTokenType;
        this->tokenValue = nullptr;
        this->quantity = nullptr;
    }

    RuleMatch::RuleMatch(int tokenType, Quantity* quantity)
    {
        this->value.tokenType = tokenType;
        this->type = RuleMatchType::RuleMatchTokenType;
        this->tokenValue = nullptr;
        this->quantity = quantity;
    }

    RuleMatch::RuleMatch(int tokenType, const char* value)
    {
        this->value.tokenType = tokenType;
        this->type = RuleMatchType::RuleMatchTokenType;
        this->tokenValue = value;
        this->quantity = nullptr;
    }

    const char* RuleMatch::getValue() {
        return this->tokenValue;
    }

    RuleMatchType RuleMatch::getType() {
        return this->type;
    }

    int RuleMatch::getTokenType() {
        return this->value.tokenType;
    }

    const char* RuleMatch::getRuleName() {
        return this->value.ruleName;
    }
}
