#include <syntax-tree.h>

namespace SyntaxTree::Token
{
    TokenMap::TokenMap() {
        this->tokenMap = new std::map<std::string, int>;
        (*this->tokenMap)["type"] = Type::TypeType;
        (*this->tokenMap)["doubleDot"] = Type::DoubleDotType;
        (*this->tokenMap)["name"] = Type::NameType;
        (*this->tokenMap)["openBrace"] = Type::OpenBraceType;
        (*this->tokenMap)["matchValue"] = Type::MatchValueType;
        (*this->tokenMap)["closeBrace"] = Type::CloseBraceType;
        (*this->tokenMap)["open"] = Type::OpenType;
        (*this->tokenMap)["close"] = Type::CloseType;
        (*this->tokenMap)["quantifier"] = Type::QuantifierType;
    }

    int TokenMap::getType(const char *typeName) {
        if (this->tokenMap->find(typeName) != this->tokenMap->end()) {
            return this->tokenMap->at(typeName);
        }

        throw new UnknownToken;
    }

    const char* TokenMap::getName(int type) {
        const char* tokenName = nullptr;
        for (auto it = this->tokenMap->begin(); it != this->tokenMap->end(); it++) {
            if (it->second == type) {
                tokenName = it->first.c_str();
                break;
            }
        }

        return tokenName;
    }
}
