#ifndef SYNTAX_TREE_POSITION_INCLUDE_H
#define SYNTAX_TREE_POSITION_INCLUDE_H

namespace SyntaxTree
{
    class Position {
    public:
        Position(int line, int column);

        int getLine();

        int getColumn();

        void setLine(int line);

        void setColumn(int column);

    private:
        int line;
        int column;
    };
}

#endif
