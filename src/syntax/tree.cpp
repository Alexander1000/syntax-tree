#include <syntax-tree.h>
#include <list>

namespace SyntaxTree::Syntax
{
    Tree::Tree() {
        this->rules = new std::list<Rule*>;
        this->tokenMap = new SyntaxTree::Token::TokenMap;
    }

    void Tree::initializeDefaults()
    {
        // @syntax-tree: start-autogenerate

        auto rule00 = new SyntaxTree::Syntax::Rule("rule");
        rule00->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("type"), "t"));
        rule00->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("doubleDot")));
        rule00->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("name")));
        rule00->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("openBrace")));
        rule00->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("matchValue")));
        rule00->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("closeBrace")));
        this->rules->push_back(rule00);

        auto rule01 = new SyntaxTree::Syntax::Rule("rule");
        rule01->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("type"), "s"));
        rule01->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("doubleDot")));
        rule01->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("name")));
        rule01->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("quantifier")));
        this->rules->push_back(rule01);

        auto rule02 = new SyntaxTree::Syntax::Rule("rule");
        rule02->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("type"), "s"));
        rule02->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("doubleDot")));
        rule02->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("name")));
        this->rules->push_back(rule02);

        auto rule03 = new SyntaxTree::Syntax::Rule("rule");
        rule03->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("type"), "t"));
        rule03->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("doubleDot")));
        rule03->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("name")));
        rule03->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("quantifier")));
        this->rules->push_back(rule03);

        auto rule04 = new SyntaxTree::Syntax::Rule("rule");
        rule04->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("type"), "t"));
        rule04->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("doubleDot")));
        rule04->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("name")));
        this->rules->push_back(rule04);

        auto rule05 = new SyntaxTree::Syntax::Rule("ruleList");
        auto q00 = new SyntaxTree::Syntax::Quantity(SyntaxTree::Syntax::QuantityType::OneOrMoreMatchType);
        rule00->addMatch(new SyntaxTree::Syntax::RuleMatch("rule", q00));
        this->rules->push_back(rule05);

        auto rule06 = new SyntaxTree::Syntax::Rule("record");
        rule06->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("name")));
        rule06->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("open")));
        rule06->addMatch(new SyntaxTree::Syntax::RuleMatch("rule"));
        rule06->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("close")));
        this->rules->push_back(rule06);

        auto rule07 = new SyntaxTree::Syntax::Rule("record");
        rule07->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("name")));
        rule07->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("open")));
        rule07->addMatch(new SyntaxTree::Syntax::RuleMatch("ruleList"));
        rule07->addMatch(new SyntaxTree::Syntax::RuleMatch(this->tokenMap->getType("close")));
        this->rules->push_back(rule07);

        auto rule08 = new SyntaxTree::Syntax::Rule("tree");
        rule08->addMatch(new SyntaxTree::Syntax::RuleMatch("record"));
        rule08->addMatch(new SyntaxTree::Syntax::RuleMatch("record"));
        this->rules->push_back(rule08);

        auto rule09 = new SyntaxTree::Syntax::Rule("tree");
        rule09->addMatch(new SyntaxTree::Syntax::RuleMatch("record"));
        this->rules->push_back(rule09);

        auto rule10 = new SyntaxTree::Syntax::Rule("tree");
        rule10->addMatch(new SyntaxTree::Syntax::RuleMatch("tree"));
        rule10->addMatch(new SyntaxTree::Syntax::RuleMatch("tree"));
        this->rules->push_back(rule10);

        // @syntax-tree: stop-autogenerate
    }
}
