#ifndef SYNTAX_TREE_SYNTAX_INCLUDE_H
#define SYNTAX_TREE_SYNTAX_INCLUDE_H

#include <syntax-tree/token.h>
#include <syntax-tree/quantity.h>
#include <list>

namespace SyntaxTree::Syntax
{
    enum RuleMatchType {
        RuleMatchTokenType,
        RuleMatchName,
    };

    enum SyntaxElementType {
        SyntaxType,
        TokenType,
        TokenListType,
    };

    class RuleMatch
    {
    public:
        explicit RuleMatch(int);
        explicit RuleMatch(int, const char*);
        explicit RuleMatch(const char*);
        RuleMatchType getType();
        int getTokenType();
        const char* getRuleName();
        const char* getValue();
    private:
        RuleMatchType type;
        union {
            int tokenType;
            const char* ruleName;
        } value;
        const char* tokenValue;
    };

    class Rule
    {
    public:
        Rule(const char*);
        void addMatch(RuleMatch*);
        std::list<RuleMatch*>* getMatches();
        const char* getName();
    private:
        const char* name;
        std::list<RuleMatch*>* matches;
    };

    class SyntaxElement
    {
    public:
        SyntaxElement(SyntaxTree::Token::Token*);
        SyntaxElement(SyntaxElement*);
        SyntaxElement(std::list<SyntaxElement*>*);
        Rule* getRule();
        SyntaxElementType getType();
        SyntaxTree::Token::Token* getToken();
        SyntaxElement* getElement();
        std::list<SyntaxElement*>* getListElements();
        void setRule(Rule*);

    private:
        Rule* rule;
        SyntaxElementType type;
        union {
            SyntaxTree::Token::Token* token;
            SyntaxElement* syntaxElement;
            std::list<SyntaxElement*>* elements;
        } data;
    };

    class Tree
    {
    public:
        Tree();
        SyntaxElement* parse(std::list<SyntaxTree::Token::Token*>*);
        virtual void initializeDefaults();

    protected:
        std::list<Rule*>* rules;
        SyntaxTree::Token::TokenMap* tokenMap;

        virtual SyntaxElement* beforeParse(std::list<SyntaxElement*>*);
        SyntaxElement* parse(std::list<SyntaxElement*>*);
        std::list<SyntaxElement*>* run_rule(Rule*, std::list<SyntaxElement*>*);
    };
}

#endif
