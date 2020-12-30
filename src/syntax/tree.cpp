#include <syntax-tree.h>
#include <list>

namespace SyntaxTree::Syntax
{
    Tree::Tree() {
        this->rules = new std::list<Rule*>;
        this->tokenMap = new SyntaxTree::Token::TokenMap;
        this->initializeDefaults();
    }

    /**
     * @syntax-tree: autogenerate
     */
    void Tree::initializeDefaults()
    {
        // do make syntax tree rules

        // rule [t:type(s) t:doubleDot t:name t:openBrace t:matchValue t:closeBrace]
//        auto rule1 = new Rule("rule");
//        rule1->addMatch(new RuleMatch(this->tokenMap->getType("type"), "s"));
//        rule1->addMatch(new RuleMatch(this->tokenMap->getType("doubleDot")));
//        rule1->addMatch(new RuleMatch(this->tokenMap->getType("name")));
//        rule1->addMatch(new RuleMatch(this->tokenMap->getType("openBrace")));
//        rule1->addMatch(new RuleMatch(this->tokenMap->getType("matchValue")));
//        rule1->addMatch(new RuleMatch(this->tokenMap->getType("closeBrace")));
//        this->rules->push_back(rule1);

        // rule [t:type(t) t:doubleDot t:name t:openBrace t:matchValue t:closeBrace]
        auto rule2 = new Rule("rule");
        rule2->addMatch(new RuleMatch(this->tokenMap->getType("type"), "t"));
        rule2->addMatch(new RuleMatch(this->tokenMap->getType("doubleDot")));
        rule2->addMatch(new RuleMatch(this->tokenMap->getType("name")));
        rule2->addMatch(new RuleMatch(this->tokenMap->getType("openBrace")));
        rule2->addMatch(new RuleMatch(this->tokenMap->getType("matchValue")));
        rule2->addMatch(new RuleMatch(this->tokenMap->getType("closeBrace")));
        this->rules->push_back(rule2);

        // rule [t:type(s) t:doubleDot t:name]
        auto rule3 = new Rule("rule");
        rule3->addMatch(new RuleMatch(this->tokenMap->getType("type"), "s"));
        rule3->addMatch(new RuleMatch(this->tokenMap->getType("doubleDot")));
        rule3->addMatch(new RuleMatch(this->tokenMap->getType("name")));
        this->rules->push_back(rule3);

        // rule [t:type(t) t:doubleDot t:name]
        auto rule4 = new Rule("rule");
        rule4->addMatch(new RuleMatch(this->tokenMap->getType("type"), "t"));
        rule4->addMatch(new RuleMatch(this->tokenMap->getType("doubleDot")));
        rule4->addMatch(new RuleMatch(this->tokenMap->getType("name")));
        this->rules->push_back(rule4);

        // ruleList [s:rule s:rule]
        auto rule5 = new Rule("ruleList");
        rule5->addMatch(new RuleMatch("rule"));
        rule5->addMatch(new RuleMatch("rule"));
        this->rules->push_back(rule5);

        // ruleList [s:ruleList s:rule]
        auto rule6 = new Rule("ruleList");
        rule6->addMatch(new RuleMatch("ruleList"));
        rule6->addMatch(new RuleMatch("rule"));
        this->rules->push_back(rule6);

        // ruleList [s:ruleList s:ruleList]
        auto rule61 = new Rule("ruleList");
        rule61->addMatch(new RuleMatch("ruleList"));
        rule61->addMatch(new RuleMatch("ruleList"));
        this->rules->push_back(rule61);

        // record [t:name t:open s:rule t:close]
        auto rule7 = new Rule("record");
        rule7->addMatch(new RuleMatch(this->tokenMap->getType("name")));
        rule7->addMatch(new RuleMatch(this->tokenMap->getType("open")));
        rule7->addMatch(new RuleMatch("rule"));
        rule7->addMatch(new RuleMatch(this->tokenMap->getType("close")));
        this->rules->push_back(rule7);

        // record [t:name t:open s:ruleList t:close]
        auto rule8 = new Rule("record");
        rule8->addMatch(new RuleMatch(this->tokenMap->getType("name")));
        rule8->addMatch(new RuleMatch(this->tokenMap->getType("open")));
        rule8->addMatch(new RuleMatch("ruleList"));
        rule8->addMatch(new RuleMatch(this->tokenMap->getType("close")));
        this->rules->push_back(rule8);

        // tree [s:record s:record]
        auto rule9 = new Rule("tree");
        rule9->addMatch(new RuleMatch("record"));
        rule9->addMatch(new RuleMatch("record"));
        this->rules->push_back(rule9);

        // tree [s:record]
        auto rule10 = new Rule("tree");
        rule10->addMatch(new RuleMatch("record"));
        this->rules->push_back(rule10);

        // tree [s:tree s:tree]
        auto rule11 = new Rule("tree");
        rule11->addMatch(new RuleMatch("tree"));
        rule11->addMatch(new RuleMatch("tree"));
        this->rules->push_back(rule11);
    }
}
