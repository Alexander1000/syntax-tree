#ifndef SYNTAX_TREE_CONFIG_INCLUDE_H
#define SYNTAX_TREE_CONFIG_INCLUDE_H

namespace SyntaxTree
{
    class Config
    {
    public:
        Config(int argc, char** argv);
        bool isHelp();
        const char* getHelpText();
        char* getSyntaxFile();
        char* getInjectFile();

    private:
        bool is_help;
        char* syntaxFile;
        char* injectFile;
    };
}

#endif
