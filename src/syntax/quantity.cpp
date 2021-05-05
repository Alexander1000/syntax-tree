#include <syntax-tree.h>
#include <list>

namespace SyntaxTree::Syntax
{
    Quantity::Quantity(QuantityType type)
    {
        this->type = type;
    }

    Quantity::Quantity(QuantityType type, int value)
    {
        this->type = type;
        this->min = value;
        this->max = value;
    }

    Quantity::Quantity(QuantityType type, int min, int max)
    {
        this->type = type;
        this->min = min;
        this->max = max;
    }

    QuantityType Quantity::getType() {
        return this->type;
    }

    int Quantity::getMin() {
        return this->min;
    }

    int Quantity::getMax() {
        return this->max;
    }
}
