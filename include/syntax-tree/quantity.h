#ifndef SYNTAX_TREE_SYNTAX_QUANTITY_INCLUDE_H
#define SYNTAX_TREE_SYNTAX_QUANTITY_INCLUDE_H

namespace SyntaxTree::Syntax
{
    enum QuantityType {
        ZeroOrOneMatchType, // ?
        OneOrMoreMatchType, // +
        AnyMatchType,       // *
        CustomMatchType,    // {n, m}
    };

    class Quantity {
    public:
        Quantity(QuantityType);
        Quantity(QuantityType, int);
        Quantity(QuantityType, int, int);
        QuantityType getType();
        int getMin();
        int getMax();

    private:
        QuantityType type;
        int min;
        int max;
    };
}

#endif
